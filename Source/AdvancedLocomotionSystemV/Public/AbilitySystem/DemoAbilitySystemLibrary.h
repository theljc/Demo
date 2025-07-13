

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DemoAbilitySystemLibrary.generated.h"

class UWidgetControllerBase;
/**
 * 
 */
UCLASS()
class ADVANCEDLOCOMOTIONSYSTEMV_API UDemoAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "AbilitySystemLibrary|WidgetController")
	static UWidgetControllerBase* GetWidgetControllerBase(const UObject* WorldContextObject);

};
