
#include "DemoGameplayTags.h"

#include "GameplayTagsManager.h"

FDemoGameplayTags FDemoGameplayTags::GameplayTags;

void FDemoGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attribute_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(
		"Attribute.Health", FString("生命值属性"));
	GameplayTags.Attribute_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		"Attribute.MaxHealth", FString("最大生命值属性"));
	GameplayTags.Attribute_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		"Attribute.Mana", FString("魔法值属性"));
	GameplayTags.Attribute_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		"Attribute.MaxMana", FString("最大魔法值属性"));
	
	GameplayTags.Abilities_RatSwarm = UGameplayTagsManager::Get().AddNativeGameplayTag(
		"Abilities.RatSwarm", FString("鼠群技能"));
	GameplayTags.Abilities_Transmission = UGameplayTagsManager::Get().AddNativeGameplayTag(
		"Abilities.Transmission", FString("传送技能"));
	GameplayTags.Abilities_Control = UGameplayTagsManager::Get().AddNativeGameplayTag(
		"Abilities.Control", FString("控制技能"));

	GameplayTags.CoolDown_RatSwarm = UGameplayTagsManager::Get().AddNativeGameplayTag(
		"CoolDown.RatSwarm", FString("鼠群技能冷却"));
	GameplayTags.CoolDown_Transmission = UGameplayTagsManager::Get().AddNativeGameplayTag(
	"CoolDown.Transmission", FString("传送技能冷却"));
	GameplayTags.CoolDown_Control = UGameplayTagsManager::Get().AddNativeGameplayTag(
	"CoolDown.Control", FString("控制技能冷却"));
	
}
