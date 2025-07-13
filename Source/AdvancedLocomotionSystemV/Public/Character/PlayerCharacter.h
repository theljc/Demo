

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase_GAS.h"
#include "PlayerCharacter.generated.h"

struct FInputActionValue;
class UInputAction;

USTRUCT(BlueprintType)
struct FPotionProps
{
	GENERATED_BODY()
public:
	// 药水瓶总数量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PotionProps")
	int32 PotionNums = 0;

	// 比如 TMap<2, 3> 表示等级为 2 的药水瓶数量有 3 个
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PotionProps")
	TMap<int32, int32> PotionMap;
	
};

/**
 * 
 */
UCLASS()
class ADVANCEDLOCOMOTIONSYSTEMV_API APlayerCharacter : public ACharacterBase_GAS
{
	GENERATED_BODY()
public:
	APlayerCharacter();
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnRep_ReplicatedMovement() override;
	

	UFUNCTION(BlueprintImplementableEvent)
	void Blueprint_PossessedBy(APlayerController* NewPlayerController);

	UPROPERTY(Replicated, BlueprintReadOnly)
	FRotator ControllerRotation;

	UPROPERTY(Replicated, BlueprintReadOnly)
	FVector Acceleration_Replicate;
	
	UFUNCTION(Server, Reliable)
	void Server_SetControllerRotation(FRotator NewRotation);

	UFUNCTION(Server, Reliable)
	void Server_SetAcceleration(FVector NewAcceleration);
	
	// void SimProxiesTurn();

protected:
	virtual void BeginPlay() override;
	
private:
	virtual void InitAbilityActorInfo() override;
};

