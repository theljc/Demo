// 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DataAsset_Base.generated.h"

class UGameplayEffect;
class UGameplayAbility;
/**
 * 
 */
UCLASS()
class ADVANCEDLOCOMOTIONSYSTEMV_API UDataAsset_Base : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default Properties")
	float InitHealth;
	
	// 初始化属性的 GE
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default Properties")
	TSubclassOf<UGameplayEffect> InitGE;

	// 受击的 Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="OnHit Properties")
	FGameplayTag OnHitActiveTag = FGameplayTag();

	// 受击触发的 GA
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="OnHit Properties")
	TSubclassOf<UGameplayAbility> GA_OnHit;

	// 防御 Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Defense Properties")
	FGameplayTag DefenseActiveTag = FGameplayTag();

	// 防御 GA
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Defense Properties")
	TSubclassOf<UGameplayAbility> GA_Defense;

	// 防御受击 Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DefenseOnHit Properties")
	FGameplayTag DefenseOnHitActiveTag = FGameplayTag();

	// 防御受击 GA
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DefenseOnHit Properties")
	TSubclassOf<UGameplayAbility> GA_DefenseOnHit;

	// Block Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Block Properties")
	FGameplayTag BlockActiveTag = FGameplayTag();

	// Block GA
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Block Properties")
	TSubclassOf<UGameplayAbility> GA_Block;

	// HitDown Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HitDown Properties")
	FGameplayTag HitDownActiveTag = FGameplayTag();

	// HitDown GA
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HitDown Properties")
	TSubclassOf<UGameplayAbility> GA_HitDown;

};
