

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widget/MainUserWidget.h"
#include "UI/WidgetController/MainWidgetController.h"
#include "MainHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class ADVANCEDLOCOMOTIONSYSTEMV_API AMainHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	// 获得主 UI 的控制器，控制器只有一个实例，保存了 PC,PS,ASC,AS 的数据
	UWidgetControllerBase* GetOverlayWidgetController(const FWidgetControllerBaseParam& WidgetControllerParam);
	// 获得 Attribute UI 的控制器
	// UAttributeWidgetController* GetAttributeWidgetController(const FWidgetControllerBaseParam& WidgetControllerParam);

	// 初始化主 UI
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

protected:
	// 作为主 UI 显示在屏幕上
	UPROPERTY()
	TObjectPtr<UMainUserWidget> MainWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UMainUserWidget> MainWidgetClass; 
	
private:

	UPROPERTY()
	TObjectPtr<UWidgetControllerBase> WidgetControllerBase;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidgetControllerBase> WidgetControllerBaseClass;
	
	// UPROPERTY()
	// TObjectPtr<UAttributeWidgetController> AttributeWidgetController;
	//
	// UPROPERTY(EditAnywhere)
	// TSubclassOf<UAttributeWidgetController> AttributeWidgetControllerClass;
};
