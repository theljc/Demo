

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_Character.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_Character : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ADVANCEDLOCOMOTIONSYSTEMV_API IInterface_Character
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="BPI Character")
	void GetWeapon(UStaticMeshComponent*& StaticMeshWeapon, USkeletalMeshComponent*& SkeletalMeshWeapon);
	
};
