

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UI/WidgetController/WidgetControllerBase.h"
#include "DemoEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class ADVANCEDLOCOMOTIONSYSTEMV_API ADemoEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADemoEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effect")
	TSubclassOf<UGameplayEffect> AppliedGameplayEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effect")
	float ActorLevel = 1.f;

	UPROPERTY()
	TObjectPtr<UWidgetControllerBase> WidgetControllerBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	
};
