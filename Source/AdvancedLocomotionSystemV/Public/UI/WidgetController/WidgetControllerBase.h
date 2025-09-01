

#pragma once

#include "CoreMinimal.h"
// #include "UObject/NoExportTypes.h"
#include "WidgetControllerBase.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class UAbilityInfo;
class UDemoAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityInfoSignature, const FDemoAbilityInfo&, Info);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPotionNumChangedSignature, int32, NewNum);

USTRUCT(BlueprintType)
struct FWidgetControllerBaseParam
{
	GENERATED_BODY();
	FWidgetControllerBaseParam(){}
	FWidgetControllerBaseParam(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS):PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS){}
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ADVANCEDLOCOMOTIONSYSTEMV_API UWidgetControllerBase : public UObject
{
	GENERATED_BODY()
public:
	// 在 UI 创建时将对应的 UI 的 PC,PS,ASC,AS 数据设置给控制器，这样控制器才能知道并使用这些数据
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerClass(const FWidgetControllerBaseParam& WidgetControllerClassParam);

	UFUNCTION(BlueprintCallable)
	virtual void BroadCastInitialValues();

	virtual void BindCallBacksDependencies();

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnResilienceChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeChangedSignature OnMaxResilienceChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FAbilityInfoSignature AbilityInfoDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnPotionNumChangedSignature OnPotionNumChanged;

	UFUNCTION(BlueprintCallable)
	void CallPotionNumChanged(int32 PotionNum);
	
protected:
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widget Data")
	TObjectPtr<UAbilityInfo> AbilityInfo;

	void OnInitializeStartupAbilities(UDemoAbilitySystemComponent* DemoASC);
	
};
