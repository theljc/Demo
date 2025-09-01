// 

#pragma once

#include "CoreMinimal.h"
#include "DataAsset_Base.h"
#include "DataAsset_EnemyBase.h"
#include "DataAsset_MeleeEnemy.generated.h"


class UDataAsset_MeleeEnemy;

USTRUCT(BlueprintType)
struct FTableRow_MeleeEnemy : public FTableRow_EnemyBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDataAsset_MeleeEnemy> DA_MeleeEnemy;
	
};


UENUM(Blueprintable, BlueprintType)
enum EMeleeEnemyCombatState : uint8
{
	EMECS_None UMETA(DisplayName = "None"),
	
	EMECS_Idle UMETA(DisplayName = "Idle"),
	EMECS_Move UMETA(DisplayName = "Move"),
	EMECS_Attack UMETA(DisplayName = "Attack"),
	EMECS_Defense UMETA(DisplayName = "Defense"),
	EMECS_DefenseOnHit UMETA(DisplayName = "Defense OnHit"),
	EMECS_OnHit UMETA(DisplayName = "OnHit"),
	EMECS_Blocked UMETA(DisplayName = "Blocked"),
	EMECS_Executed UMETA(DisplayName = "Executed"),
	EMECS_Dead UMETA(DisplayName = "Dead"),
	
};

UENUM(Blueprintable, BlueprintType)
enum EMeleeEnemySenseState : uint8
{
	EMESS_None UMETA(DisplayName = "None"),
	
	EMESS_Attack UMETA(DisplayName = "Attack"),
	EMESS_Investigate UMETA(DisplayName = "Investigate"),
	EMESS_Pursuit UMETA(DisplayName = "Pursuit"),
	EMESS_Patrol UMETA(DisplayName = "Patrol"),

};

// UENUM(Blueprintable, BlueprintType)
// enum EMeleeEnemyAttackType : uint8
// {
// 	EMEAT_None UMETA(DisplayName = "None"),
// 	// 每次攻击会有攻击类型，根据这个类型判断玩家的受击动画
// 	EMEAT_MeleeAttack UMETA(DisplayName = "Melee Attack"),
// 	EMEAT_MeleeAttack_Block UMETA(DisplayName = "Melee Attack Block"),
// 	EMEAT_MeleeAttack_HitDown UMETA(DisplayName = "Melee Attack HitDown"),
// 	EMEAT_RangedAttack UMETA(DisplayName = "Ranged Attack"),
// 	EMEAT_RangedAttack_Block UMETA(DisplayName = "Ranged Attack Block"),
// 	EMEAT_RangedAttack_HitDown UMETA(DisplayName = "Ranged Attack HitDown"),
// 	
// };

UENUM(Blueprintable, BlueprintType)
enum EMeleeEnemyOnHitType : uint8
{
	EMEOHT_None UMETA(DisplayName = "None"),
	// Boss 的受击类型
	EMEOHT_NormalHit UMETA(DisplayName = "Normal Hit"),
	EMEOHT_BlockedHit UMETA(DisplayName = "Blocked Hit"),
	EMEOHT_HitDown UMETA(DisplayName = "HitDown"),
	
};

// 每个攻击动作的数据
USTRUCT(BlueprintType)
struct FMeleeEnemyAttackAbilityInfo : public FEnemyAttackAbilityInfoBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttackActiveTag = FGameplayTag();

	// 伤害
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackDamage = 0.f;

	// 冷却
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CoolDown = 0.f;

	// 削弱玩家的耐力值
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float WeakeningEndurance = 0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> AttackMontages;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EEnemyAttackType> AttackType = EEAT_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> AttackGA;

	// 攻击命中后施加伤害的 GE
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> GE_ApplyDamage;

	// 攻击命中后削韧的 GE
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> GE_ApplyWeakeningResilience;
	
};

// 受击时根据受击类型播放不同的受击动画
USTRUCT(BlueprintType)
struct FMeleeEnemyOnHitAbilityInfo : public FEnemyOnHitAbilityInfoBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EEnemyOverlayState> MeleeEnemyOverlayState = EEOS_None;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EMeleeEnemyOnHitType> OnHitType = EMEOHT_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EOnHitDirection> OnHitDirection = OHD_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> OnHitMontage;
	
};

USTRUCT(BlueprintType)
struct FMeleeEnemyBlockAbilityInfo : public FCharacterBlockAbilityInfo
{
	GENERATED_BODY()
	
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ADVANCEDLOCOMOTIONSYSTEMV_API UDataAsset_MeleeEnemy : public UDataAsset_EnemyBase
{
	GENERATED_BODY()
public:
	// IInterface_DataAsset 接口
	virtual UDataAsset_MeleeEnemy* GetDataAsset_MeleeEnemy_Implementation() override;
	
	// 战斗状态
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default Properties")
	TEnumAsByte<EMeleeEnemyCombatState> MeleeEnemyCombatState = EMECS_None;

	// 感知状态
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default Properties")
	TEnumAsByte<EMeleeEnemySenseState> MeleeEnemySenseState = EMESS_None;

	// 攻击技能，数组保存多种攻击技能
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attack Properties")
	TArray<FMeleeEnemyAttackAbilityInfo> AttackAbilityInfo;

	// 受击信息
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="OnHit Properties")
	TArray<FMeleeEnemyOnHitAbilityInfo> OnHitAbilityInfo;

	// 防御动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Defense Properties")
	TObjectPtr<UAnimMontage> DefenseMontage;

	// 防御受击动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DefenseOnHit Properties")
	TObjectPtr<UAnimMontage> DefenseOnHitMontage;

	// Block 动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Block Properties")
	TArray<FMeleeEnemyBlockAbilityInfo> BlockAbilityInfo;

	// HitDown 动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HitDown Properties")
	TObjectPtr<UAnimMontage> HitDownMontage;
	
public:
	virtual FGameplayTagContainer GetAllOtherActiveTags() override;
	virtual FGameplayTagContainer GetAllAttackActiveTags() override;
	virtual TArray<TSubclassOf<UGameplayAbility>> GetAllAttackAbilities() override;
	virtual TArray<TSubclassOf<UGameplayAbility>> GetAllOtherAbilities() override;
	
};
