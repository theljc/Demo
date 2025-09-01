// 

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstanceBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMapLoadDelegate, UWorld*, NewWorld);

/**
 * 
 */
UCLASS()
class ADVANCEDLOCOMOTIONSYSTEMV_API UGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void PreLoadMap();
	
	UFUNCTION(BlueprintCallable)
	void PostLoadMap(UWorld* NewWorld);

	UPROPERTY(BlueprintAssignable)
	FOnMapLoadDelegate OnMapLoad;

};
