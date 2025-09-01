// 

#pragma once

#include "CoreMinimal.h"
#include "DataAsset_Base.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DataAsset_Player.generated.h"

enum EOnHitDirection : uint8;
class UGameplayEffect;
class UGameplayAbility;
class UDataAsset_Player;

USTRUCT(BlueprintType)
struct FTableRow_Player : public FTableRow_CharacterBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDataAsset_Player> DA_Player;
	
};

// 玩家的所有覆盖状态
UENUM(BlueprintType)
enum EPlayerOverlayState : uint8
{
	EPOS_None UMETA(DisplayName = "None"),
	
	EPOS_Default UMETA(DisplayName = "Default"),
	EPOS_Sword UMETA(DisplayName = "Sword"),
	
};

// 玩家战斗时的状态
UENUM(BlueprintType)
enum EPlayerStateEnum : uint8
{
	EPS_None UMETA(DisplayName = "None"),
	
	// 待机状态
	EPS_Idle UMETA(DisplayName = "Idle"),
	// // 移动状态
	// EPS_Move UMETA(DisplayName = "Move"),
	
	// 攻击状态
	EPS_Attack UMETA(DisplayName = "Attack"),
	// 防御状态
	EPS_Defense UMETA(DisplayName = "Defense"),
	// 防御受击状态
	EPS_DefenseOnHit UMETA(DisplayName = "Defense OnHit"),
	// 受击状态
	EPS_OnHit UMETA(DisplayName = "OnHit"),
	// 被打断
	EPS_Blocked UMETA(DisplayName = "Blocked"),
	// 治疗状态
	EPS_Healing UMETA(DisplayName = "Healing"),
	// 韧性值为 0 时的破防状态
	EPS_ResilienceBlock UMETA(DisplayName = "Resilience Block"), 
	// 倒地状态
	EPS_HitDown UMETA(DisplayName = "Hit Down"),

	// 表示玩家正在切换持刀和非持刀状态
	EPS_ChangeState UMETA(DisplayName = "Change State"),
	// 处决状态
	EPS_Execution UMETA(DisplayName="Execution"),
	//  附身状态
	EPS_Possession UMETA(DisplayName="Possession"),
	//  闪避状态
	EPS_Dodge UMETA(DisplayName="Dodge"),
	// 死亡状态
	EPS_Dead UMETA(DisplayName = "Dead"), 
	
};

// 每次攻击会有攻击类型，根据这个类型判断敌人的受击动画
UENUM(BlueprintType)
enum EPlayerAttackType : uint8
{
	EPAT_None UMETA(DisplayName = "None"),
	
	EPAT_Normal UMETA(DisplayName = "Normal"),
	EPAT_Block UMETA(DisplayName = "Block"),
	EPAT_HitDown UMETA(DisplayName = "HitDown"),
	
};

USTRUCT(BlueprintType)
struct FPlayerAttackAbilityInfo : public FCharacterAttackAbilityInfo
{
	GENERATED_BODY()

	// 激活 GA 的 Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttackActiveTag = FGameplayTag();

	// 伤害
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackDamage = 0.f;

	// 冷却
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CoolDown = 0.f;

	// 削韧值
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float WeakeningResilience = 0.f;

	// 攻击动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> AttackMontages;

	// 攻击类型
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EPlayerAttackType> AttackType = EPAT_None;

	// 攻击的 GA
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> AttackGA;

	// 攻击命中后施加伤害的 GE
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> GE_ApplyDamage;

	// 攻击命中后削韧的 GE
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> GE_ApplyWeakeningResilience;

	// 以当次攻击作为结束时的冷却时间
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> GE_AttackCoolDown;
	
};

// 玩家的受击类型
UENUM(BlueprintType)
enum EPlayerOnHitType : uint8
{
	EPOHT_None UMETA(DisplayName = "None"),

	EPOHT_NormalHit UMETA(DisplayName = "Normal Hit"),
	EPOHT_BlockedHit UMETA(DisplayName = "Blocked Hit"),
	EPOHT_HitDown UMETA(DisplayName = "HitDown"),
	
};

USTRUCT(BlueprintType)
struct FPlayerOnHitAbilityInfo : public FCharacterOnHitAbilityInfo
{
	GENERATED_BODY()

	// 玩家的覆盖状态
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EPlayerOverlayState> PlayerOverlayState = EPlayerOverlayState::EPOS_None;
	
	// 受击类型
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EPlayerOnHitType> OnHitType = EPlayerOnHitType::EPOHT_None;

	// 受击方向
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EOnHitDirection> OnHitDirection = EOnHitDirection::OHD_None;
	
	// 受击动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> OnHitMontage;
	
};

USTRUCT(BlueprintType)
struct FPlayerBlockAbilityInfo : public FCharacterBlockAbilityInfo
{
	GENERATED_BODY()
	
};

// 玩家闪避时的方向，直接在蓝图中配置
UENUM(BlueprintType)
enum EPlayerDodgeDirection : uint8
{
	EPDD_None UMETA(DisplayName = "None"),
	
	EPDD_Front UMETA(DisplayName = "Front"),
	EPDD_Back UMETA(DisplayName = "Back"),
	EPDD_Left UMETA(DisplayName = "Left"),
	EPDD_Right UMETA(DisplayName = "Right"),
	
};

// 玩家的移动状态
UENUM(BlueprintType)
enum EPlayerMovementState : uint8
{
	EPMS_None UMETA(DisplayName = "None"),
	
	// 处于地面
	EPMS_Ground UMETA(DisplayName = "Ground"),
	// 处于空中
	EPMS_InAir UMETA(DisplayName = "InAir"),
	// 处于攀爬
	EPMS_Mantle UMETA(DisplayName="Mantle"),
	// 处于布娃娃
	EPMS_Ragdoll UMETA(DisplayName="Ragdoll"),
	
};

// 闪避信息
USTRUCT(BlueprintType)
struct FPlayerDodgeAbilityInfo
{
	GENERATED_BODY()

	// 移动状态
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EPlayerMovementState> MovementState = EPlayerMovementState::EPMS_None;
	
	// 闪避方向
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EPlayerDodgeDirection> DodgeDirection = EPlayerDodgeDirection::EPDD_None;

	// 闪避动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> DodgeMontage;
	
};

/**
 * 
 */
UCLASS(BlueprintType)
class ADVANCEDLOCOMOTIONSYSTEMV_API UDataAsset_Player : public UDataAsset_Base
{
	GENERATED_BODY()
public:
	// IInterface_DataAsset 接口
	virtual UDataAsset_Player* GetDataAsset_Player_Implementation() override;
	
	// 玩家战斗状态
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default Properties")
	TEnumAsByte<EPlayerStateEnum> PlayerCombatState = EPlayerStateEnum::EPS_None;

	// 攻击技能，数组保存多种攻击技能
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attack Properties")
	TArray<FPlayerAttackAbilityInfo> AttackAbilityInfo;

	// 受击信息
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="OnHit Properties")
	TArray<FPlayerOnHitAbilityInfo> OnHitAbilityInfo;

	// 防御动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Defense Properties")
	TObjectPtr<UAnimMontage> DefenseMontage;

	// 防御受击动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DefenseOnHit Properties")
	TObjectPtr<UAnimMontage> DefenseOnHitMontage;

	// Block 动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Block Properties")
	TArray<FPlayerBlockAbilityInfo> BlockAbilityInfo;

	// 闪避
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dodge Properties")
	FGameplayTag DodgeActiveTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dodge Properties")
	TArray<FPlayerDodgeAbilityInfo> DodgeAbilityInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dodge Properties")
	TSubclassOf<UGameplayAbility> GA_Dodge;

	// 弹反
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Parry Properties")
	FGameplayTag ParryActiveTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Parry Properties")
	TObjectPtr<UAnimMontage> ParryMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Parry Properties")
	TSubclassOf<UGameplayAbility> GA_Parry;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Parry Properties")
	FGameplayTag ParryMessageTag = FGameplayTag();

	// 韧性值为 0 时的破防状态
	// 硬直恢复时间
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ResilienceBlock Properties")
	float ResilienceBlockRestoreTime = 0.0f;

	// 从硬直状态恢复时的 GE
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ResilienceBlock Properties")
	TSubclassOf<UGameplayEffect> GE_ResilienceBlockRestore;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ResilienceBlock Properties")
	FGameplayTag ResilienceBlockActiveTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ResilienceBlock Properties")
	TObjectPtr<UAnimMontage> ResilienceBlockMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ResilienceBlock Properties")
	TSubclassOf<UGameplayAbility> GA_ResilienceBlock;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ResilienceBlock Properties")
	FGameplayTag ResilienceBlockMessageTag = FGameplayTag();

	// 被击倒动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="HitDown Properties")
	TObjectPtr<UAnimMontage> HitDownMontage;

	// 治疗
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Heal Properties")
	FGameplayTag HealActiveTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Heal Properties")
	TSubclassOf<UGameplayAbility> GA_Heal;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Heal Properties")
	TObjectPtr<UAnimMontage> HealMontage;
	
public:
	virtual FGameplayTagContainer GetAllOtherActiveTags() override;
	virtual FGameplayTagContainer GetAllAttackActiveTags() override;
	virtual TArray<TSubclassOf<UGameplayAbility>> GetAllAttackAbilities() override;
	virtual TArray<TSubclassOf<UGameplayAbility>> GetAllOtherAbilities() override;
	
};
