

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase_GAS.h"
#include "UI/WidgetController/MainWidgetController.h"
#include "EnemyCharacter.generated.h"

class UDataAsset_Boss;
class UBehaviorTree;
class UWidgetComponent;

/**
 * 
 */
UCLASS()
class ADVANCEDLOCOMOTIONSYSTEMV_API AEnemyCharacter : public ACharacterBase_GAS
{
	GENERATED_BODY()
public:
	AEnemyCharacter();

	virtual void PossessedBy(AController* NewController) override;

	// 重写 ICombatInterface 接口的函数
	// virtual int32 GetPlayerLevel_Implementation() override;
	//
	// virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	//
	// virtual AActor* GetCombatTarget_Implementation() override;
	// End ICombatInterface
	
	void HitReactTagChanged(const FGameplayTag CallBackTag, int32 NewCount);

	UFUNCTION(BlueprintImplementableEvent)
	void OnASCInit();

	UFUNCTION(BlueprintCallable)
	void CreateDataInstance();

	UPROPERTY(BlueprintReadOnly, Category="Combat")
	bool bHitReacting = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	float LifeSpan = 5.f;

	UPROPERTY(BlueprintReadWrite, Category="Combat")
	TObjectPtr<AActor> CombatTarget;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnResilienceChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxResilienceChanged;
	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	// 初始化敌人类的属性
	virtual void InitializeDefaultAttributes() const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Default Class")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	// UPROPERTY(EditDefaultsOnly)
	// TSubclassOf<UDataAsset_Boss> BossDataClass;

	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	// TObjectPtr<UDataAsset_Boss> BossData;
	
	// UPROPERTY(EditDefaultsOnly, Category="AI")
	// TObjectPtr<UBehaviorTree> BehaviorTree;

	// UPROPERTY()
	// TObjectPtr<AAuraAIController> AuraAIController;
};
