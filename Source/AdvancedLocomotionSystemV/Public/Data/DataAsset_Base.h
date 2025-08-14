// 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "Interface/Interface_DataAsset.h"
#include "DataAsset_Base.generated.h"

class UGameplayEffect;
class UGameplayAbility;


USTRUCT(BlueprintType)
struct FTableRow_CharacterBase : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
};

UENUM(BlueprintType)
enum EOnHitDirection : uint8
{
	OHD_None UMETA(DisplayName = "None"),

	OHD_Front UMETA(DisplayName = "Front"),
	OHD_Back UMETA(DisplayName = "Back"),
	OHD_Left UMETA(DisplayName = "Left"),
	OHD_Right UMETA(DisplayName = "Right"),
};

USTRUCT(BlueprintType)
struct FCharacterAttackAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttackMessageTag = FGameplayTag();
	
};

USTRUCT(BlueprintType)
struct FCharacterOnHitAbilityInfo
{
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType)
struct FCharacterBlockAbilityInfo
{
	GENERATED_BODY()
	
	// Block 方向
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EOnHitDirection> BlockDirection;
	
	// Block 动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> BlockMontage;
	
};


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ADVANCEDLOCOMOTIONSYSTEMV_API UDataAsset_Base : public UDataAsset, public IInterface_DataAsset
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

	// 受击 Message Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="OnHit Properties")
	FGameplayTag OnHitMessageTag = FGameplayTag();

	// 防御 Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Defense Properties")
	FGameplayTag DefenseActiveTag = FGameplayTag();

	// 防御 GA
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Defense Properties")
	TSubclassOf<UGameplayAbility> GA_Defense;

	// 防御 Message Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Defense Properties")
	FGameplayTag DefenseMessageTag = FGameplayTag();
	
	// 防御受击 Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DefenseOnHit Properties")
	FGameplayTag DefenseOnHitActiveTag = FGameplayTag();

	// 防御受击 GA
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DefenseOnHit Properties")
	TSubclassOf<UGameplayAbility> GA_DefenseOnHit;

	// 防御受击 Message Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DefenseOnHit Properties")
	FGameplayTag DefenseOnHitMessageTag = FGameplayTag();
	
	// Block Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Block Properties")
	FGameplayTag BlockActiveTag = FGameplayTag();

	// Block GA
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Block Properties")
	TSubclassOf<UGameplayAbility> GA_Block;

	// Block Message Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Block Properties")
	FGameplayTag BlockMessageTag = FGameplayTag();
	
	// HitDown Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HitDown Properties")
	FGameplayTag HitDownActiveTag = FGameplayTag();

	// HitDown GA
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HitDown Properties")
	TSubclassOf<UGameplayAbility> GA_HitDown;

	// HitDown Message Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HitDown Properties")
	FGameplayTag HitDownMessageTag = FGameplayTag();

public:
	// 除了攻击 Tag 之外的其它 Tags
	UFUNCTION(BlueprintPure)
	virtual FGameplayTagContainer GetAllOtherActiveTags();
	
	// 所有攻击 Tag
	UFUNCTION(BlueprintPure)
	virtual FGameplayTagContainer GetAllAttackActiveTags();

	// 所有攻击 GA
	UFUNCTION(BlueprintPure)
	virtual TArray<TSubclassOf<UGameplayAbility>> GetAllAttackAbilities();

	// 除攻击外的 GA
	UFUNCTION(BlueprintPure)
	virtual TArray<TSubclassOf<UGameplayAbility>> GetAllOtherAbilities();
	
};
