#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Character/PlayerCharacter.h"
#include "Data/DataAsset_Player.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateBase.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

// UENUM(Blueprintable, BlueprintType)
// enum class EPlayerStateEnum : uint8
// {
// 	EPS_None UMETA(DisplayName="None"),
// 	
// 	EPS_Normal UMETA(DisplayName="Normal"), // 正常状态
// 	EPS_Attack UMETA(DisplayName="Attack"), // 攻击状态
// 	EPS_Dead UMETA(DisplayName="Dead"), // 死亡状态
// 	EPS_Execution UMETA(DisplayName="Execution"), // 处决状态
// 	EPS_Possession UMETA(DisplayName="Possession"), //  附身状态
// 	EPS_Mantle UMETA(DisplayName="Mantle"), // 攀爬状态
// 	// EPS_Sword UMETA(DisplayName="Sword"), // 持刀状态，这个状态在 ALS 中存在，切换时使用 ALS 的状态，判断时使用这个状态
// 	
// };
/**
 * 
 */
UCLASS()
class ADVANCEDLOCOMOTIONSYSTEMV_API APlayerStateBase : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	APlayerStateBase();

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet;}

	// 计算药水瓶的数量
	UFUNCTION(BlueprintCallable)
	void CalcHealthPotionProps(int32 Level);
	
	// FORCEINLINE int32 GetPlayerLevel() const { return Level;}
	// FORCEINLINE int32 GetPlayerXP() const { return XP;}

	// FOnPlayerStatChanged OnXPChangedDelegate;
	// FOnPlayerStatChanged OnLevelChangedDelegate;
	
	// void AddToXP(const int32 InXP);
	// void AddToLevel(const int32 InLevel);
	
	// void SetXP(const int32 InXP);
	// void SetLevel(const int32 InLevel);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPotionProps HealthPotionProps;

	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EPlayerStateEnum> PlayerStateEnum;
	
	// 在切换关卡时保存玩家当前生命值
	// UPROPERTY(BlueprintReadWrite)
	// float SavedHealth;

	// UPROPERTY(EditDefaultsOnly)
	// TObjectPtr<ULevelUpInfo> LevelUpInfo;

	
// private:
// 	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
// 	int32 Level = 1;
//
// 	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_XP)
// 	int32 XP = 1;
// 	
// 	UFUNCTION()
// 	void OnRep_Level(int32 OldLevel);
//
// 	UFUNCTION()
// 	void OnRep_XP(int32 OldXP);
};
