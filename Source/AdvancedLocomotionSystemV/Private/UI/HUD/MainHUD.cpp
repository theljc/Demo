


#include "UI/HUD/MainHUD.h"

UWidgetControllerBase* AMainHUD::GetOverlayWidgetController(const FWidgetControllerBaseParam& WidgetControllerParam)
{
	// 如果主 UI 的控制器存在则返回，不存在则创建
	if (WidgetControllerBase == nullptr)
	{
		// 控制器需要 FAuraWidgetControllerParam 类型的数据
		WidgetControllerBase = NewObject<UWidgetControllerBase>(this, WidgetControllerBaseClass);
		WidgetControllerBase->SetWidgetControllerClass(WidgetControllerParam);
		// 绑定回调函数
		WidgetControllerBase->BindCallBacksDependencies();
	}
	
	return WidgetControllerBase;
}

void AMainHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(MainWidgetClass, TEXT("Main Widget Class uninitialized, please fill out BP_AuraHUD"));
	checkf(WidgetControllerBaseClass, TEXT("Widget Controller Base Class uninitialized, please fill out BP_AuraHUD"));
	
	// 创建主 UI
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), MainWidgetClass);
	MainWidget = Cast<UMainUserWidget>(Widget);
	
	// 获得主 UI 的控制器，不存在则创建
	const FWidgetControllerBaseParam WidgetControllerParam(PC, PS, ASC, AS);
	UWidgetControllerBase* WidgetController = GetOverlayWidgetController(WidgetControllerParam); 
	
	// 将主 UI 的控制器设置为 WidgetController
	MainWidget->SetWidgetController(WidgetController);
	
	// 向所有小部件发出通知，初始化值
	WidgetControllerBase->BroadCastInitialValues();
	
	// 主 UI 添加到视口
	Widget->AddToViewport();
}
