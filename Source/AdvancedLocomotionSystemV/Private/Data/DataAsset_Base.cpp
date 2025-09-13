// 


#include "Data/DataAsset_Base.h"

#include "Misc/DataValidation.h"

EDataValidationResult UDataAsset_Base::IsDataValid(class FDataValidationContext& Context) const
{
	if (InitHealth < 0.f)
	{
		Context.AddError(FText::FromString(TEXT("初始生命值不能小于 0")));
		return EDataValidationResult::Invalid;
	}

	if (InitResilience < 0.f)
	{
		Context.AddError(FText::FromString(TEXT("初始韧性值不能小于 0")));
		return EDataValidationResult::Invalid;
	}
	
	return EDataValidationResult::Valid;
}

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
