

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DemoAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer&);
DECLARE_MULTICAST_DELEGATE_OneParam(FAbilitiesGiven, UDemoAbilitySystemComponent*);
DECLARE_DELEGATE_OneParam(FForEachAbilities, const FGameplayAbilitySpec&);

/**
 * 
 */
UCLASS()
class ADVANCEDLOCOMOTIONSYSTEMV_API UDemoAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityActorInfoSet();
	
	// 添加角色初始拥有的 GA
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities);
	// 添加角色初始拥有的 GA（被动技能）
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& PassiveAbilities);

	// 按住指定按键时激活 GA
	void AbilityInputTagHeld(const FGameplayTag& Tags);
	// 松开指定按键时不会激活 GA ，但也需要通知
	void AbilityInputTagReleased(const FGameplayTag& Tags);

	// 从 GA Spec 中获得其对应设置的 Ability Tag
	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& Spec);
	// 从 GA Spec 中获得其对应设置的 Input Tag
	// static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& Spec);

	// 判断技能是否已经被给予
	bool bStartupAbilitiesGiven = false;
	
	FEffectAssetTags EffectAssetTags;

	// 委托，当技能被给与角色时广播
	FAbilitiesGiven AbilitiesGivenDelegate;

	// void ForEachAbilities(const FForEachAbilities& Delegate);

protected:
	// RPC 函数，绑定委托时使客户端也能够调用此函数
	UFUNCTION(Client, Reliable)
	void ClientOnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle) const;

	// 客户端会调用此函数激活技能
	virtual void OnRep_ActivateAbilities() override;
};
