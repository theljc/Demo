// 


#include "Data/DataAsset_Base.h"

FGameplayTagContainer UDataAsset_Base::GetAllOtherActiveTags()
{
	return FGameplayTagContainer();
}

FGameplayTagContainer UDataAsset_Base::GetAllAttackActiveTags()
{
	return FGameplayTagContainer();
}

TArray<TSubclassOf<UGameplayAbility>> UDataAsset_Base::GetAllAttackAbilities()
{
	return TArray<TSubclassOf<UGameplayAbility>>();
}

TArray<TSubclassOf<UGameplayAbility>> UDataAsset_Base::GetAllOtherAbilities()
{
	return TArray<TSubclassOf<UGameplayAbility>>();
}
