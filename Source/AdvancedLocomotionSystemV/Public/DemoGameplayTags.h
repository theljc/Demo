

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */

struct FDemoGameplayTags
{
public:
	static const FDemoGameplayTags& Get(){return GameplayTags;}
	static void InitializeNativeGameplayTags();

	FGameplayTag Attribute_Health;
	FGameplayTag Attribute_MaxHealth;
	FGameplayTag Attribute_Mana;
	FGameplayTag Attribute_MaxMana;

	FGameplayTag Abilities_RatSwarm;
	FGameplayTag Abilities_Transmission;
	FGameplayTag Abilities_Control;

	FGameplayTag CoolDown_RatSwarm;
	FGameplayTag CoolDown_Transmission;
	FGameplayTag CoolDown_Control;
	
private:
	static FDemoGameplayTags GameplayTags;
	
};