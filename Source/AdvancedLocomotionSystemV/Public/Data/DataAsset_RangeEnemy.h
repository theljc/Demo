// 

#pragma once

#include "CoreMinimal.h"
#include "DataAsset_EnemyBase.h"
#include "DataAsset_RangeEnemy.generated.h"


USTRUCT(BlueprintType)
struct FTableRow_RangeEnemy : public FTableRow_EnemyBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDataAsset_RangeEnemy> DA_RangeEnemy;
	
};


UENUM(Blueprintable, BlueprintType)
enum ERangeEnemyCombatState : uint8
{
	ERECS_None UMETA(DisplayName = "None"),
	
	ERECS_Idle UMETA(DisplayName = "Idle"),
	ERECS_Move UMETA(DisplayName = "Move"),
	ERECS_Attack UMETA(DisplayName = "Attack"),
	ERECS_Defense UMETA(DisplayName = "Defense"),
	ERECS_DefenseOnHit UMETA(DisplayName = "Defense OnHit"),
	ERECS_OnHit UMETA(DisplayName = "OnHit"),
	ERECS_Blocked UMETA(DisplayName = "Blocked"),
	ERECS_Executed UMETA(DisplayName = "Executed"),
	ERECS_Dead UMETA(DisplayName = "Dead"),
	
};

UENUM(Blueprintable, BlueprintType)
enum ERangeEnemySenseState : uint8
{
	ERESS_None UMETA(DisplayName = "None"),
	
	ERESS_Attack UMETA(DisplayName = "Attack"),
	ERESS_Investigate UMETA(DisplayName = "Investigate"),
	ERESS_Pursuit UMETA(DisplayName = "Pursuit"),
	ERESS_Patrol UMETA(DisplayName = "Patrol"),

};

UENUM(Blueprintable, BlueprintType)
enum ERangeEnemyAttackType : uint8
{
	EREAT_None UMETA(DisplayName = "None"),
	// 每次攻击会有攻击类型，根据这个类型判断玩家的受击动画
	EREAT_MeleeAttack UMETA(DisplayName = "Melee Attack"),
	EREAT_MeleeAttack_Block UMETA(DisplayName = "Melee Attack Block"),
	EREAT_MeleeAttack_HitDown UMETA(DisplayName = "Melee Attack HitDown"),
	EREAT_RangedAttack UMETA(DisplayName = "Ranged Attack"),
	EREAT_RangedAttack_Block UMETA(DisplayName = "Ranged Attack Block"),
	EREAT_RangedAttack_HitDown UMETA(DisplayName = "Ranged Attack HitDown"),
	
};

UENUM(Blueprintable, BlueprintType)
enum ERangeEnemyOnHitType : uint8
{
	EREOHT_None UMETA(DisplayName = "None"),
	// Boss 的受击类型
	EREOHT_NormalHit UMETA(DisplayName = "Normal Hit"),
	EREOHT_BlockedHit UMETA(DisplayName = "Blocked Hit"),
	EREOHT_HitDown UMETA(DisplayName = "HitDown"),
	
};

// 每个攻击动作的数据
USTRUCT(BlueprintType)
struct FRangeEnemyAttackAbilityInfo : public FEnemyAttackAbilityInfoBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttackActiveTag = FGameplayTag();

	// 伤害
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackDamage;

	// 冷却
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CoolDown;

	// 削弱玩家的耐力值
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float WeakeningEndurance;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> AttackMontages;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<ERangeEnemyAttackType> AttackType = EREAT_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> AttackGA;

	// 攻击命中后施加伤害的 GE
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> GE_ApplyDamage;
	
};

// 受击时根据受击类型播放不同的受击动画
USTRUCT(BlueprintType)
struct FRangeEnemyOnHitAbilityInfo : public FEnemyOnHitAbilityInfoBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EEnemyOverlayState> RangeEnemyOverlayState;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<ERangeEnemyOnHitType> OnHitType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EOnHitDirection> OnHitDirection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> OnHitMontage;
	
};

USTRUCT(BlueprintType)
struct FRangeEnemyBlockAbilityInfo : public FCharacterBlockAbilityInfo
{
	GENERATED_BODY()
	
};

/**
 * 
 */
UCLASS()
class ADVANCEDLOCOMOTIONSYSTEMV_API UDataAsset_RangeEnemy : public UDataAsset_EnemyBase
{
	GENERATED_BODY()
public:
	// IInterface_DataAsset 接口
	virtual UDataAsset_RangeEnemy* GetDataAsset_RangeEnemy_Implementation() override;
	
	// 战斗状态
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default Properties")
	TEnumAsByte<ERangeEnemyCombatState> RangeEnemyCombatState;

	// 感知状态
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default Properties")
	TEnumAsByte<ERangeEnemySenseState> RangeEnemySenseState;

	// 攻击技能，数组保存多种攻击技能
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attack Properties")
	TArray<FRangeEnemyAttackAbilityInfo> AttackAbilityInfo;

	// 受击信息
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="OnHit Properties")
	TArray<FRangeEnemyOnHitAbilityInfo> OnHitAbilityInfo;

	// 防御动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Defense Properties")
	TObjectPtr<UAnimMontage> DefenseMontage;

	// 防御受击动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DefenseOnHit Properties")
	TObjectPtr<UAnimMontage> DefenseOnHitMontage;

	// Block 动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Block Properties")
	TArray<FRangeEnemyBlockAbilityInfo> BlockAbilityInfo;

	// HitDown 动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HitDown Properties")
	TObjectPtr<UAnimMontage> HitDownMontage;
	
public:
	virtual FGameplayTagContainer GetAllOtherActiveTags() override;
	virtual FGameplayTagContainer GetAllAttackActiveTags() override;
	
};
