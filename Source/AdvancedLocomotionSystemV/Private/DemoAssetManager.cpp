


#include "DemoAssetManager.h"

UDemoAssetManager& UDemoAssetManager::Get()
{
	check(GEngine);
	
	UDemoAssetManager* AssetManager = Cast<UDemoAssetManager>(GEngine->AssetManager);
	return *AssetManager;
}

void UDemoAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
}
