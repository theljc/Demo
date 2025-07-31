

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataAsset.h"
#include "DataAsset_Boss.generated.h"

enum EOnHitDirection : uint8;
class UDataAsset_Boss;

USTRUCT(BlueprintType)
struct FTableRow_Boss : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDataAsset_Boss> DA_Boss;
	
};


UENUM(Blueprintable, BlueprintType)
enum EBossCombatState : uint8
{
	EBCS_None UMETA(DisplayName = "None"),
	
	EBCS_Idle UMETA(DisplayName = "Idle"),
	EBCS_Move UMETA(DisplayName = "Move"),
	EBCS_Attack UMETA(DisplayName = "Attack"),
	EBCS_OnHit UMETA(DisplayName = "OnHit"),
	EBCS_Blocked UMETA(DisplayName = "Blocked"),
	EBCS_Executed UMETA(DisplayName = "Executed"),
	EBCS_Dead UMETA(DisplayName = "Dead"),
	
};

UENUM(Blueprintable, BlueprintType)
enum EBossSenseState : uint8
{
	EBSS_None UMETA(DisplayName = "None"),
	
	EBSS_MeleeRange UMETA(DisplayName = "MeleeRange"),
	EBSS_RemoteRange UMETA(DisplayName = "RemoteRange"),
	EBSS_Pursuit UMETA(DisplayName = "Pursuit"),
	EBSS_Patrol UMETA(DisplayName = "Patrol"),

};

UENUM(Blueprintable, BlueprintType)
enum EBossAttackType : uint8
{
	EBAT_None UMETA(DisplayName = "None"),
	// 每次攻击会有攻击类型，根据这个类型判断玩家的受击动画
	EBAT_MeleeAttack UMETA(DisplayName = "Melee Attack"),
	EBAT_MeleeAttack_Block UMETA(DisplayName = "Melee Attack Block"),
	EBAT_MeleeAttack_HitDown UMETA(DisplayName = "Melee Attack HitDown"),
	EBAT_RangedAttack UMETA(DisplayName = "Ranged Attack"),
	EBAT_RangedAttack_Block UMETA(DisplayName = "Ranged Attack Block"),
	EBAT_RangedAttack_HitDown UMETA(DisplayName = "Ranged Attack HitDown"),
	
};

UENUM(Blueprintable, BlueprintType)
enum EBossOnHitType : uint8
{
	EBOHT_None UMETA(DisplayName = "None"),
	// Boss 的受击类型
	EBOHT_NormalHit UMETA(DisplayName = "Normal Hit"),
	EBOHT_BlockedHit UMETA(DisplayName = "Blocked Hit"),
	EBOHT_HitDown UMETA(DisplayName = "HitDown"),
	
};

// 每个攻击动作的数据
USTRUCT(BlueprintType)
struct FBossAttackAbilityInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttackActiveTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> AttackMontages;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EBossAttackType> AttackType = EBossAttackType::EBAT_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> AttackGA;
	
};

// 受击时根据受击类型播放不同的受击动画
USTRUCT(BlueprintType)
struct FBossOnHitAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EBossOnHitType> OnHitType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EOnHitDirection> OnHitDirection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> OnHitMontage;
	
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ADVANCEDLOCOMOTIONSYSTEMV_API UDataAsset_Boss : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default Properties")
	float RestoreTime;
	
	// 初始化属性的 GE
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default Properties")
	TSubclassOf<UGameplayEffect> InitGE;
	
	// 战斗状态
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default Properties")
	TEnumAsByte<EBossCombatState> BossCombatState;

	// 感知状态
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default Properties")
	TEnumAsByte<EBossSenseState> BossSenseState;

	// 攻击技能，数组保存多种攻击技能
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attack Properties")
	TArray<FBossAttackAbilityInfo> AttackAbilityInfo;

	// 受击的 Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="OnHit Properties")
	FGameplayTag OnHitActiveTag = FGameplayTag();

	// 受击信息
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="OnHit Properties")
	TArray<FBossOnHitAbilityInfo> OnHitAbilityInfo;

	// 防御 Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Defense Properties")
	FGameplayTag DefenseActiveTag = FGameplayTag();

	// 防御动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Defense Properties")
	TObjectPtr<UAnimMontage> DefenseMontage;
	
};
