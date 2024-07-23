// Fill out your copyright notice in the Description page of Project Settings.


#include "GASBlueprintFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemLog.h"

struct FGameplayAbilitySpec;
class UGameplayAbility;

bool UGASBlueprintFunctionLibrary::CanActivateAbility(UAbilitySystemComponent* Target,FGameplayAbilitySpecHandle AbilitySpecHandle)
{
	FGameplayTagContainer FailureTags;
	FGameplayAbilitySpec* Spec = Target->FindAbilitySpecFromHandle(AbilitySpecHandle);
	if (!Spec)
	{
		ABILITY_LOG(Warning, TEXT("TryActivateAbility called with invalid Handle"));
		return false;
	}
	
	UGameplayAbility* Ability = Spec->Ability;
	if (!Ability)
	{
		ABILITY_LOG(Warning, TEXT("TryActivateAbility called with invalid Ability"));
		return false;
	}
	
	return Ability->CanActivateAbility(AbilitySpecHandle, Target->AbilityActorInfo.Get(), nullptr, nullptr, &FailureTags);
}
