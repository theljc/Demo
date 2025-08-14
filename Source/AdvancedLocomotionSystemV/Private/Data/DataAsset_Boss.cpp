


#include "Data/DataAsset_Boss.h"

UDataAsset_Boss* UDataAsset_Boss::GetDataAsset_Boss_Implementation()
{
	return this;
}

FGameplayTagContainer UDataAsset_Boss::GetAllOtherActiveTags()
{
	FGameplayTagContainer AllOtherActiveTags;
	TArray<FGameplayTag> Tags;
	
	Tags.Add(OnHitActiveTag);
	Tags.Add(DefenseActiveTag);
	Tags.Add(DefenseOnHitActiveTag);
	Tags.Add(BlockActiveTag);
	Tags.Add(HitDownActiveTag);
	
	return AllOtherActiveTags.CreateFromArray(Tags);
}

FGameplayTagContainer UDataAsset_Boss::GetAllAttackActiveTags()
{
	FGameplayTagContainer AllAttackActiveTags;
	TArray<FGameplayTag> Tags;
	
	for (FBossAttackAbilityInfo AttackInfo : AttackAbilityInfo)
	{
		Tags.Add(AttackInfo.AttackActiveTag);
	}
	
	return AllAttackActiveTags.CreateFromArray(Tags);
}

TArray<TSubclassOf<UGameplayAbility>> UDataAsset_Boss::GetAllAttackAbilities()
{
	TArray<TSubclassOf<UGameplayAbility>> AllAttackAbilities;
	for (FBossAttackAbilityInfo AttackInfo : AttackAbilityInfo)
	{
		AllAttackAbilities.Add(AttackInfo.AttackGA);
	}

	return AllAttackAbilities;
}

TArray<TSubclassOf<UGameplayAbility>> UDataAsset_Boss::GetAllOtherAbilities()
{
	TArray<TSubclassOf<UGameplayAbility>> AllAttackAbilities;
	AllAttackAbilities.Add(GA_OnHit);
	AllAttackAbilities.Add(GA_Defense);
	AllAttackAbilities.Add(GA_DefenseOnHit);
	AllAttackAbilities.Add(GA_Block);
	AllAttackAbilities.Add(GA_HitDown);
	
	return AllAttackAbilities;
}
