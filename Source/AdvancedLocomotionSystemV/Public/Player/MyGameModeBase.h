

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class ACharacterBase_GAS;
/**
 * 
 */
UCLASS()
class ADVANCEDLOCOMOTIONSYSTEMV_API AMyGameModeBase : public AGameMode
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void TravelTest();
	
	TObjectPtr<ACharacterBase_GAS> CharacterBase;
	
};
