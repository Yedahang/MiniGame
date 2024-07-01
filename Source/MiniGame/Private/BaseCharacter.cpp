// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	UAbilitySystemComponent* MyAbilitySystemComponent = this->FindComponentByClass<UAbilitySystemComponent>();
	if(MyAbilitySystemComponent)
	{
		MyAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetHPAttribute()).AddUObject(this,&ABaseCharacter::OnHealthAttributeChanged);

		MyAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetMPAttribute()).AddUObject(this,&ABaseCharacter::OnMPAttributeChanged);
		MyAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetStrengthAttribute()).AddUObject(this,&ABaseCharacter::OnStrengthAttributeChanged);	
		
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UAbilitySystemComponent* MyAbilitySystemComponent = this->FindComponentByClass<UAbilitySystemComponent>();
	if(MyAbilitySystemComponent)
	{
		MyAbilitySystemComponent->BindAbilityActivationToInputComponent(PlayerInputComponent,
			FGameplayAbilityInputBinds(FString(),FString(),
					FString("EGASAbilityInputID"),-1,-1));
		
	}

}

void ABaseCharacter::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	//if(HasAuthority())
	//{
	HPChangeEvent.Broadcast(Data.NewValue);
	//}
	if (GetLocalRole() == ROLE_Authority)
	{
		UE_LOG(LogTemp, Log, TEXT("Server: Health changed to %f"), Data.NewValue);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Client: Health changed to %f"), Data.NewValue);
	}
}

void ABaseCharacter::OnMPAttributeChanged(const FOnAttributeChangeData& Data)
{
	if(HasAuthority())
	{
		MPChangeEvent.Broadcast(Data.NewValue);
	}
}

void ABaseCharacter::OnStrengthAttributeChanged(const FOnAttributeChangeData& Data)
{
	if(HasAuthority())
	{
		StrengthChangeEvent.Broadcast(Data.NewValue);
	}
}

FGameplayAbilityInfo ABaseCharacter::GameplayAbilityInfo(TSubclassOf<UBaseGameplayAbility> AbilityClass, int level)
{
	UAbilitySystemComponent* MyAbilitySystemComponent = this->FindComponentByClass<UAbilitySystemComponent>();

	UBaseGameplayAbility* AbilityInstance = AbilityClass->GetDefaultObject<UBaseGameplayAbility>();
	if(MyAbilitySystemComponent && AbilityInstance)
	{
		return AbilityInstance->GetAbilityInfo(level);
	}
	return FGameplayAbilityInfo();
}

