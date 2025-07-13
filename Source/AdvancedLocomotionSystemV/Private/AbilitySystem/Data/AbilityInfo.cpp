


#include "AbilitySystem/Data/AbilityInfo.h"

FDemoAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& Tag)
{
	for (auto AbilityInfo : AbilityInformation)
	{
		if (AbilityInfo.AbilityTag == Tag)
		{
			return AbilityInfo;
		}
	}
	return FDemoAbilityInfo();
}
