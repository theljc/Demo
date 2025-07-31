

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Data/DataAsset_Boss.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DemoAbilitySystemLibrary.generated.h"

class UWidgetControllerBase;

USTRUCT(BlueprintType)
struct FGameplayEventData_Modify : public FGameplayEventData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayAbilityTriggerPayload)
	FBossAttackAbilityInfo AttackAbilityInfo;
};

/**
 * 
 */
UCLASS()
class ADVANCEDLOCOMOTIONSYSTEMV_API UDemoAbilitySystemLibrary : public UAbilitySystemBlueprintLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "AbilitySystemLibrary|WidgetController")
	static UWidgetControllerBase* GetWidgetControllerBase(const UObject* WorldContextObject);
	
};
