

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_DataAsset.generated.h"

class UDataAsset_RangeEnemy;
class UDataAsset_Boss;
class UDataAsset_Player;
class UDataAsset_MeleeEnemy;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_DataAsset : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ADVANCEDLOCOMOTIONSYSTEMV_API IInterface_DataAsset
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UDataAsset_Boss* GetDataAsset_Boss();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UDataAsset_Player* GetDataAsset_Player();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UDataAsset_MeleeEnemy* GetDataAsset_MeleeEnemy();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UDataAsset_RangeEnemy* GetDataAsset_RangeEnemy();
	
};
