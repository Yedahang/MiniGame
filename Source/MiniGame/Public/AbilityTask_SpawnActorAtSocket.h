// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/Actor.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_SpawnActorAtSocket.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpawnActorDelegate, AActor*, SpawnedActor);

/**
 * 
 */


UCLASS()
class MINIGAME_API UAbilityTask_SpawnActorAtSocket : public UAbilityTask
{
	GENERATED_BODY()

	UAbilityTask_SpawnActorAtSocket(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(BlueprintAssignable)
	FSpawnActorDelegate	Success;

	/** Called when we can't spawn: on clients or potentially on server if they fail to spawn (rare) */
	UPROPERTY(BlueprintAssignable)
	FSpawnActorDelegate	DidNotSpawn;
	
	/** Spawn new Actor on the network authority (server) */
	UFUNCTION(BlueprintCallable, meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"), Category="Ability|Tasks")
	static UAbilityTask_SpawnActorAtSocket* SpawnActorAtSocket(UGameplayAbility* OwningAbility,FTransform SpawnTransform, TSubclassOf<AActor> Class);

	UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"), Category = "Abilities")
	bool BeginSpawningActor(UGameplayAbility* OwningAbility, FGameplayAbilityTargetDataHandle TargetData, TSubclassOf<AActor> Class, AActor*& SpawnedActor);

	UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"), Category = "Abilities")
	void FinishSpawningActor(UGameplayAbility* OwningAbility, FGameplayAbilityTargetDataHandle TargetData, AActor* SpawnedActor);

protected:
	FTransform SpawnTransform;
};
