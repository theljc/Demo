

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "DemoAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDLOCOMOTIONSYSTEMV_API UDemoAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static UDemoAssetManager& Get();
	
protected:
	virtual void StartInitialLoading() override;
	
};
