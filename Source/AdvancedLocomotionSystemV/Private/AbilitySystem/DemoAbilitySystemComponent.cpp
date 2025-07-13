


#include "AbilitySystem/DemoAbilitySystemComponent.h"

#include "AbilitySystem/Abilities/DemoGameplayAbility.h"

void UDemoAbilitySystemComponent::AbilityActorInfoSet()
{
	// GE 被应用时绑定客户端调用函数
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UDemoAbilitySystemComponent::ClientOnEffectApplied);

}

void UDemoAbilitySystemComponent::ClientOnEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle) const
{
	// 在 GE 应用的时候，获得 Tag 的信息保存到 TagContainer
	FGameplayTagContainer TagContainer;
	GameplayEffectSpec.GetAllAssetTags(TagContainer);
	// 广播委托，传入保存的 Tag 信息
	EffectAssetTags.Broadcast(TagContainer);
}

void UDemoAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	// 遍历数组，激活 GA
	for (const TSubclassOf<UGameplayAbility> AbilityClass : Abilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UDemoGameplayAbility* DemoGameplayAbility = Cast<UDemoGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(DemoGameplayAbility->StartUpInputTag);
			GiveAbility(AbilitySpec);
		}
	}
	// 表示技能已经被给予
	bStartupAbilitiesGiven = true;
	AbilitiesGivenDelegate.Broadcast(this);
}

void UDemoAbilitySystemComponent::AddCharacterPassiveAbilities(
	const TArray<TSubclassOf<UGameplayAbility>>& PassiveAbilities)
{
	// 遍历数组，激活 GA (被动技能)
	for (const TSubclassOf<UGameplayAbility> AbilityClass : PassiveAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

void UDemoAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& Tags)
{
	if (!Tags.IsValid())
	{
		return;
	}
	// 遍历所有已激活的技能
	for (auto& AbilitySpec:GetActivatableAbilities())
	{
		// 判断激活的技能是否有指定的 Tag
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(Tags))
		{
			// 表示有按键被按下
			AbilitySpecInputPressed(AbilitySpec);
			// 如果未激活状态则激活 GA
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UDemoAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& Tags)
{
	if (!Tags.IsValid())
	{
		return;
	}
	
	for (auto& AbilitySpec:GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(Tags))
		{
			// 表示松开了按键
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

FGameplayTag UDemoAbilitySystemComponent::GetAbilityTagFromSpec(const FGameplayAbilitySpec& Spec)
{
	if (Spec.Ability)
	{
		// 遍历 GA 中的所有 Tag
		for (FGameplayTag Tag : Spec.Ability.Get()->AbilityTags)
		{
			// 每个技能使用 Abilities 分类中的不同 Tag，所以可以直接根据 Abilities 分类，找到对应的 Tag
			if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities"))))
			{
				return Tag;
			}
		}
	}
	return FGameplayTag();
}

// FGameplayTag UDemoAbilitySystemComponent::GetInputTagFromSpec(const FGameplayAbilitySpec& Spec)
// {
// 	for (FGameplayTag Tag : Spec.DynamicAbilityTags)
// 	{
// 		if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("InputTag"))))
// 		{
// 			return Tag;
// 		}
// 	}
// 	return FGameplayTag();
// }

void UDemoAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	// 加判断是为了防止服务器再次调用一遍
	if (!bStartupAbilitiesGiven)
	{
		bStartupAbilitiesGiven = true;
		AbilitiesGivenDelegate.Broadcast(this);
	}
	
}
