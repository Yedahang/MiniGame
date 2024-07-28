// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "AsyncTaskGameplayTagAddedRemoved.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayTagAddedRemoved, FGameplayTag, Tag);
/**
 * 一个蓝图节点，用于自动注册监听器，监听 FGameplayTags 的添加和移除。
 * 适用于在 Blueprint/UMG 中使用。
 */
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = AsyncTask))
class MINIGAME_API UAsyncTaskGameplayTagAddedRemoved : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnGameplayTagAddedRemoved OnTagAdded;

	UPROPERTY(BlueprintAssignable)
	FOnGameplayTagAddedRemoved OnTagRemoved;

	//监听GameplayTags的添加和移除
	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly = "true"))
	static UAsyncTaskGameplayTagAddedRemoved* ListenForGameplayTagAddedOrRemoved(UAbilitySystemComponent* AbilitySystemComponent,FGameplayTagContainer InTags);

	// 当你希望异步任务结束时，必须手动调用此函数。
	// 对于 UMG 小部件，你可以在小部件的 Destruct 事件中调用它。
	UFUNCTION(BlueprintCallable)
	void EndTask();
protected:
	UPROPERTY()
	UAbilitySystemComponent* ASC;

	FGameplayTagContainer Tags;
	
	virtual void TagChanged(const FGameplayTag Tag, int32 NewCount);
};
