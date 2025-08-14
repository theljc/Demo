// 


#include "Data/DataAsset_RangeEnemy.h"

UDataAsset_RangeEnemy* UDataAsset_RangeEnemy::GetDataAsset_RangeEnemy_Implementation()
{
	return this;
}

FGameplayTagContainer UDataAsset_RangeEnemy::GetAllOtherActiveTags()
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

FGameplayTagContainer UDataAsset_RangeEnemy::GetAllAttackActiveTags()
{
	FGameplayTagContainer AllAttackActiveTags;
	TArray<FGameplayTag> Tags;
	
	for (FRangeEnemyAttackAbilityInfo AttackInfo : AttackAbilityInfo)
	{
		Tags.Add(AttackInfo.AttackActiveTag);
	}
	
	return AllAttackActiveTags.CreateFromArray(Tags);
}

TArray<TSubclassOf<UGameplayAbility>> UDataAsset_RangeEnemy::GetAllAttackAbilities()
{
	TArray<TSubclassOf<UGameplayAbility>> AllAttackAbilities;
	for (FRangeEnemyAttackAbilityInfo AttackInfo : AttackAbilityInfo)
	{
		AllAttackAbilities.Add(AttackInfo.AttackGA);
	}

	return AllAttackAbilities;
}

TArray<TSubclassOf<UGameplayAbility>> UDataAsset_RangeEnemy::GetAllOtherAbilities()
{
	TArray<TSubclassOf<UGameplayAbility>> AllAttackAbilities;
	AllAttackAbilities.Add(GA_OnHit);
	AllAttackAbilities.Add(GA_Defense);
	AllAttackAbilities.Add(GA_DefenseOnHit);
	AllAttackAbilities.Add(GA_Block);
	AllAttackAbilities.Add(GA_HitDown);
	
	return AllAttackAbilities;
}
