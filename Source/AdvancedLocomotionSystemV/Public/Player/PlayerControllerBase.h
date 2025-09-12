

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UDemoAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class ADVANCEDLOCOMOTIONSYSTEMV_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
public:
	APlayerControllerBase();
	virtual void PlayerTick(const float DeltaTime) override;

	virtual void ClientSetHUD_Implementation(TSubclassOf<AHUD> NewHUDClass) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> DemoContext;

	// UPROPERTY(EditAnywhere, Category="Input")
	// TObjectPtr<UInputAction> MoveAction;
	
	// UPROPERTY(EditAnywhere, Category="Input")
	// TObjectPtr<UInputAction> ShiftAction;

	void Move(const FInputActionValue& InputActionValue);

	// 按住 shift 时可以在指定位置释放技能
	// void ShiftPressed() {bShiftKeyDown = true;}
	// void ShiftReleased() {bShiftKeyDown = false;}
	// bool bShiftKeyDown = false;

	// 调用 AuraASC 组件的函数来处理按下，松开，按住按键时是否激活 GA
	// void AbilityInputTagPressed(FGameplayTag InputTag);
	// void AbilityInputTagReleased(FGameplayTag InputTag);
	// void AbilityInputTagHeld(FGameplayTag InputTag);

	UDemoAbilitySystemComponent* GetASC();
	
	// UPROPERTY(EditAnywhere, Category="Input")
	// TObjectPtr<UAuraInputConfig> InputConfig;
	
	UPROPERTY()
	TObjectPtr<UDemoAbilitySystemComponent> AbilitySystemComponent;
	
};
