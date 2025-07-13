

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUserWidget.generated.h"


/**
 * 
 */
UCLASS()
class ADVANCEDLOCOMOTIONSYSTEMV_API UMainUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	// 设置 WidgetController，在 MVC 模式中，WidgetController 作为控制所有 Widget 的控制器
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	// 保存 WidgetController
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

	// 创建一个 LAN 服务器，并打开指定的关卡
	UFUNCTION(BlueprintCallable)
	void OpenLevel_LAN(const FString& LevelPath);

	// 加入一个 LAN 服务器
	UFUNCTION(BlueprintCallable)
	void JoinLevel_LAN(const FString& ServerAddress);
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};
