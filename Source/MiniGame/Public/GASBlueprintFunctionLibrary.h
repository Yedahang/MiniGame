// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GASBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAME_API UGASBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "GASFunctionLibrary")
	static bool CanActivateAbility(UAbilitySystemComponent* Target,FGameplayAbilitySpecHandle AbilitySpecHandle);
};
