// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTask_SpawnActorAtSocket.h"
#include "AbilitySystemComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AbilityTask_SpawnActorAtSocket)


UAbilityTask_SpawnActorAtSocket::UAbilityTask_SpawnActorAtSocket(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

UAbilityTask_SpawnActorAtSocket* UAbilityTask_SpawnActorAtSocket::SpawnActorAtSocket(UGameplayAbility* OwningAbility, FTransform SpawnTransform, TSubclassOf<AActor> Class)
{
	UAbilityTask_SpawnActorAtSocket* MyObj = NewAbilityTask<UAbilityTask_SpawnActorAtSocket>(OwningAbility);
	MyObj->SpawnTransform = SpawnTransform;
	return MyObj;
}

// ---------------------------------------------------------------------------------------

bool UAbilityTask_SpawnActorAtSocket::BeginSpawningActor(UGameplayAbility* OwningAbility,FGameplayAbilityTargetDataHandle TargetData, TSubclassOf<AActor> InClass, AActor*& SpawnedActor)
{
	if (Ability && Ability->GetCurrentActorInfo()->IsNetAuthority() && ShouldBroadcastAbilityTaskDelegates())
	{
		UWorld* const World = GEngine->GetWorldFromContextObject(OwningAbility, EGetWorldErrorMode::LogAndReturnNull);
		if (World)
		{

			SpawnedActor = World->SpawnActorDeferred<AActor>(InClass, FTransform::Identity, NULL, NULL, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		}
	}
	
	if (SpawnedActor == nullptr)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			DidNotSpawn.Broadcast(nullptr);
		}
		return false;
	}

	return true;
}

void UAbilityTask_SpawnActorAtSocket::FinishSpawningActor(UGameplayAbility* OwningAbility, FGameplayAbilityTargetDataHandle TargetData, AActor* SpawnedActor)
{
	if (SpawnedActor)
	{
		SpawnedActor->FinishSpawning(this->SpawnTransform);
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			Success.Broadcast(SpawnedActor);
		}
	}

	EndTask();
}

// ---------------------------------------------------------------------------------------


