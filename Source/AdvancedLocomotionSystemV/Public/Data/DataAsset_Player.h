// 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DataAsset_Player.generated.h"

enum EOnHitDirection : uint8;
class UGameplayEffect;
class UGameplayAbility;
class UDataAsset_Player;

USTRUCT(BlueprintType)
struct FTableRow_Player : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDataAsset_Player> DA_Player;
	
};

// 玩家战斗时的状态
UENUM(BlueprintType)
enum EPlayerStateEnum : uint8
{
	EPS_None UMETA(DisplayName = "None"),
	
	// 待机状态
	EPS_Idle UMETA(DisplayName = "Idle"),
	// 移动状态
	EPS_Move UMETA(DisplayName = "Move"),
	// 攻击状态
	EPS_Attack UMETA(DisplayName = "Attack"),
	// 受击状态
	EPS_OnHit UMETA(DisplayName = "OnHit"),
	// 被打断
	EPS_Blocked UMETA(DisplayName = "Blocked"),
	// 处决状态
	EPS_Execution UMETA(DisplayName="Execution"),
	//  附身状态
	EPS_Possession UMETA(DisplayName="Possession"),
	// 攀爬状态
	EPS_Mantle UMETA(DisplayName="Mantle"),
	// 死亡状态
	EPS_Dead UMETA(DisplayName = "Dead"), 
	
};

UENUM(BlueprintType)
enum EPlayerAttackType : uint8
{
	EPAT_None UMETA(DisplayName = "None"),
	
	// 每次攻击会有攻击类型，根据这个类型判断敌人的受击动画
	EPAT_MeleeAttack UMETA(DisplayName = "Melee Attack"),
	EPAT_MeleeAttack_Block UMETA(DisplayName = "Melee Attack Block"),
	EPAT_MeleeAttack_HitDown UMETA(DisplayName = "Melee Attack HitDown"),

	// 玩家的远程攻击类型（未使用）
	EPAT_RangedAttack UMETA(DisplayName = "Ranged Attack"),
	EPAT_RangedAttack_Block UMETA(DisplayName = "Ranged Attack Block"),
	EPAT_RangedAttack_HitDown UMETA(DisplayName = "Ranged Attack HitDown"),
	
};

USTRUCT(BlueprintType)
struct FPlayerAttackAbilityInfo
{
	GENERATED_BODY()

	// 激活 GA 的 Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttackActiveTag = FGameplayTag();

	// 攻击动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> AttackMontages;

	// 攻击类型
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EPlayerAttackType> AttackType = EPAT_None;

	// 攻击的 GA
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> AttackGA;
	
};


UENUM(BlueprintType)
enum EPlayerOnHitType : uint8
{
	EPOHT_None UMETA(DisplayName = "None"),

	// 玩家的受击类型
	EPOHT_NormalHit UMETA(DisplayName = "Normal Hit"),
	EPOHT_BlockedHit UMETA(DisplayName = "Blocked Hit"),
	EPOHT_HitDown UMETA(DisplayName = "HitDown"),
	
};

USTRUCT(BlueprintType)
struct FPlayerOnHitAbilityInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EPlayerOnHitType> OnHitType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EOnHitDirection> OnHitDirection;
	
	// 通过受击类型映射受击动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> OnHitMontage;
	
};

/**
 * 
 */
UCLASS(BlueprintType)
class ADVANCEDLOCOMOTIONSYSTEMV_API UDataAsset_Player : public UDataAsset
{
	GENERATED_BODY()
public:
	// 初始生命值
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default Properties")
	float Health;
	
	// 初始化属性的 GE
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default Properties")
	TSubclassOf<UGameplayEffect> InitGE;

	// 玩家战斗状态
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default Properties")
	TEnumAsByte<EPlayerStateEnum> PlayerCombatState;

	// 攻击技能，数组保存多种攻击技能
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attack Properties")
	TArray<FPlayerAttackAbilityInfo> AttackAbilityInfo;

	// 受击的 Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="OnHit Properties")
	FGameplayTag OnHitActiveTag = FGameplayTag();

	// 受击信息
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="OnHit Properties")
	TArray<FPlayerOnHitAbilityInfo> OnHitAbilityInfo;

	// 防御 Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Defense Properties")
	FGameplayTag DefenseActiveTag = FGameplayTag();

	// 防御动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Defense Properties")
	TObjectPtr<UAnimMontage> DefenseMontage;
	
};
