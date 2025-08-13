// 


#include "Data/DataAsset_MeleeEnemy.h"

UDataAsset_MeleeEnemy* UDataAsset_MeleeEnemy::GetDataAsset_MeleeEnemy_Implementation()
{
	return this;
}

FGameplayTagContainer UDataAsset_MeleeEnemy::GetAllOtherActiveTags()
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

FGameplayTagContainer UDataAsset_MeleeEnemy::GetAllAttackActiveTags()
{
	FGameplayTagContainer AllAttackActiveTags;
	TArray<FGameplayTag> Tags;
	
	for (FMeleeEnemyAttackAbilityInfo AttackInfo : AttackAbilityInfo)
	{
		Tags.Add(AttackInfo.AttackActiveTag);
	}
	
	return AllAttackActiveTags.CreateFromArray(Tags);
}
