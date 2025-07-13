#include "AbilitySystem/AttributeSet/AttributeSetBase.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
//#include "GameplayEffectExtension.h"
//#include <Runtime/Engine/Public/Net/UnrealNetwork.h>

UAttributeSetBase::UAttributeSetBase()
	: Health(1.f)
	, MaxHealth(1.f)
	, CoolDown(1.f)
	, Damage(1.f)
{
	
}

void UAttributeSetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	// 生命值改变时
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	
}

void UAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		float a = GetHealth();
		SetHealth(FMath::Clamp(a, 0, GetMaxHealth()));
		// SetHealth(FMath::Clamp(Data.EvaluatedData.Magnitude, 0, GetMaxHealth()));
	}
	
}

void UAttributeSetBase::PostAttributeChange(const FGameplayAttribute& Attribute,
	float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	// if (Attribute == GetMaxHealthAttribute())
	// {
		// SetHealth(FMath::Clamp(GetHealth(), 0, GetMaxHealth()));
	
	// 	float a = GetHealth();
	// 	float b = a;
	// 	SetHealth(GetMaxHealth());
	// }
	
}

void UAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 声明需要复制的变量
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, MaxHealth, COND_None, REPNOTIFY_Always);

}

void UAttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	// 处理在 RepNotify 时的属性
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, Health, OldHealth);
}

void UAttributeSetBase::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, MaxHealth, OldMaxHealth);
}
