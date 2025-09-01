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
	Tags.Add(ResilienceBlockActiveTag);
	Tags.Add(HealActiveTag);
	
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

TArray<TSubclassOf<UGameplayAbility>> UDataAsset_Player::GetAllAttackAbilities()
{
	TArray<TSubclassOf<UGameplayAbility>> AllAttackAbilities;
	for (FPlayerAttackAbilityInfo AttackInfo : AttackAbilityInfo)
	{
		AllAttackAbilities.Add(AttackInfo.AttackGA);
	}

	return AllAttackAbilities;
}

TArray<TSubclassOf<UGameplayAbility>> UDataAsset_Player::GetAllOtherAbilities()
{
	TArray<TSubclassOf<UGameplayAbility>> AllAttackAbilities;
	AllAttackAbilities.Add(GA_OnHit);
	AllAttackAbilities.Add(GA_Defense);
	AllAttackAbilities.Add(GA_DefenseOnHit);
	AllAttackAbilities.Add(GA_Block);
	AllAttackAbilities.Add(GA_HitDown);
	AllAttackAbilities.Add(GA_Dodge);
	AllAttackAbilities.Add(GA_Parry);
	AllAttackAbilities.Add(GA_ResilienceBlock);
	AllAttackAbilities.Add(GA_Heal);
	
	return AllAttackAbilities;
}
