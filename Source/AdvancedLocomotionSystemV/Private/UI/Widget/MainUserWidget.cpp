


#include "UI/Widget/MainUserWidget.h"

#include "Kismet/GameplayStatics.h"

void UMainUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	
	WidgetControllerSet();
}

void UMainUserWidget::OpenLevel_LAN(const FString& LevelPath)
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->ServerTravel(LevelPath);
	}
}

void UMainUserWidget::JoinLevel_LAN(const FString& ServerAddress)
{
	UGameplayStatics::OpenLevel(GetWorld(), *ServerAddress);
}
