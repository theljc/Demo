#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AbilitySystem/AttributeSet/AttributeSetBase.h"
// #include "AbilitySystemInterface.h"
#include "CharacterBase_GAS.generated.h"

USTRUCT(BlueprintType)
struct FMyTargetData : public FGameplayAbilityTargetData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AActor*> TargetArray;
	
	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
	
};


UCLASS()
class ADVANCEDLOCOMOTIONSYSTEMV_API ACharacterBase_GAS : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool GetCooldownRemainingForTag(FGameplayTagContainer CooldownTags, float& TimeRemaining, float& CooldownDuration);

	// Sets default values for this character's properties
	ACharacterBase_GAS();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	float TurnThreshold = 0.5f;
	FRotator ProxyRotationLastFrame;
	FRotator ProxyRotation;
	float ProxyYaw;
	float CalculateSpeed();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void InitAbilityActorInfo();
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Abilities")
	// 	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> PreloadedAbilities;
	
	// UPROPERTY()
	// 	UAttributeSetBase* AttributeSet;

	// 应用 GE
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> DefaultGameplayEffectClass, float Level) const;
	// 初始化所有的默认属性
	virtual void InitializeDefaultAttributes() const;
	// 只在服务器上执行，此函数会调用 AuraASC 的 AddCharacterAbilities 激活初始 GA
	void AddCharacterAbilities() const;
	
	// UPROPERTY(Category = "Combat", EditAnywhere, BlueprintReadOnly)
	// TObjectPtr<USkeletalMeshComponent> Weapon;

	// UPROPERTY(Category = "Combat", EditAnywhere)
	// FName WeaponTipSocketName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attribute")
	TSubclassOf<UGameplayEffect> DefaultStartUpGameplayEffectClass;

	// UPROPERTY(BlueprintReadWrite)
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	/** Returns total time and remaining time for cooldown tags. Returns false if no active cooldowns found */
	// UFUNCTION(BlueprintCallable, Category = "Abilities")
	// 	bool GetCooldownRemainingForTag(FGameplayTagContainer CooldownTags, float& TimeRemaining, float& CooldownDuration);
	
	UFUNCTION(BlueprintCallable, Category = "Test")
		void PrintStr();

private:
	// UPROPERTY(EditAnywhere, category = "Abilities")
	// TArray<TSubclassOf<UGameplayAbility>> StartUpAbilities;

	UPROPERTY(EditAnywhere, category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartUpPassiveAbilities;
};
