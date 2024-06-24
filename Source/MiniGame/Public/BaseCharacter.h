// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameplayAbility.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"
struct FOnAttributeChangeData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeEvent, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMPChangeEvent, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStrengthChangeEvent, float, NewValue);
UCLASS()
class MINIGAME_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintAssignable,Category="Ability")
	FOnHealthChangeEvent HPChangeEvent;

	UPROPERTY(BlueprintAssignable,Category="Ability")
	FOnMPChangeEvent MPChangeEvent;

	UPROPERTY(BlueprintAssignable,Category="Ability")
	FOnStrengthChangeEvent StrengthChangeEvent;
	
	void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);
	
	void OnMPAttributeChanged(const FOnAttributeChangeData& Data);

	void OnStrengthAttributeChanged(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintCallable,Category="BaseCharacter")
	FGameplayAbilityInfo GameplayAbilityInfo(TSubclassOf<UBaseGameplayAbility>AbilityClass, int level);
};
