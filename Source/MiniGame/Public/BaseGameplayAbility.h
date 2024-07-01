// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BaseGameplayAbility.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECostType : uint8
{
	HP,
	MP,
	Strength
};

UENUM(BlueprintType)
enum class EGASAbilityInputID : uint8
{
	None UMETA(DisplayName="None"),
	Melee UMETA(DisplayName="Melee")
};

USTRUCT(BlueprintType)
struct FGameplayAbilityInfo 
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AbilityInfo")
	float CD;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AbilityInfo")
	ECostType  CostType;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AbilityInfo")
	float CostValue;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AbilityInfo")
	UMaterialInstance * IconMaterial;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AbilityInfo")
	TSubclassOf<UBaseGameplayAbility> AbilityClass;

	FGameplayAbilityInfo();
	FGameplayAbilityInfo(float CD, ECostType  CostType,float CostValue,UMaterialInstance * IconMaterial,TSubclassOf<UBaseGameplayAbility> AbilityClass);
};


UCLASS()
class MINIGAME_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AbilityInfo")
	UMaterialInstance * IconMaterial;

	UFUNCTION(BlueprintCallable,Category="AbilityInfo")
	FGameplayAbilityInfo GetAbilityInfo(int level);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="GAS|Binding")
	TMap<EGASAbilityInputID,TSubclassOf<UGameplayAbility>> GASBinding;
};
