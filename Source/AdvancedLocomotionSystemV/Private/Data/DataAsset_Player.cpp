// 


#include "Data/DataAsset_Player.h"

UDataAsset_Player* UDataAsset_Player::GetDataAsset_Player_Implementation()
{
	return this;
}

FGameplayTagContainer UDataAsset_Player::GetAllOtherActiveTags()
{
	FGameplayTagContainer AllOtherActiveTags;
	TArray<FGameplayTag> Tags;
	
	Tags.Add(OnHitActiveTag);
	Tags.Add(DefenseActiveTag);
	Tags.Add(DefenseOnHitActiveTag);
	Tags.Add(BlockActiveTag);
	Tags.Add(HitDownActiveTag);
	Tags.Add(DodgeActiveTag);
	Tags.Add(ParryActiveTag);
	
	return AllOtherActiveTags.CreateFromArray(Tags);
}

FGameplayTagContainer UDataAsset_Player::GetAllAttackActiveTags()
{
	FGameplayTagContainer AllAttackActiveTags;
	TArray<FGameplayTag> Tags;
	
	for (FPlayerAttackAbilityInfo AttackInfo : AttackAbilityInfo)
	{
		Tags.Add(AttackInfo.AttackActiveTag);
	}
	
	return AllAttackActiveTags.CreateFromArray(Tags);
}
