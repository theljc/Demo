// 

#pragma once

#include "CoreMinimal.h"
#include "DataAsset_Base.h"
#include "DataAsset_EnemyBase.generated.h"


USTRUCT(BlueprintType)
struct FTableRow_EnemyBase : public FTableRow_CharacterBase
{
	GENERATED_USTRUCT_BODY()
	
};

// 敌人的所有覆盖状态
UENUM(BlueprintType)
enum EEnemyOverlayState : uint8
{
	EEOS_None UMETA(DisplayName = "None"),
	
	EEOS_Default UMETA(DisplayName = "Default"),
	EEOS_Sword UMETA(DisplayName = "Sword"),
	EEOS_Rifle UMETA(DisplayName = "Rifle"),
	EEOS_Scythe UMETA(DisplayName = "Scythe"),
	EEOS_ScytheFly UMETA(DisplayName = "Scythe Fly"),
	
};

// 敌人的移动状态
UENUM(BlueprintType)
enum EEnemyMovementState : uint8
{
	EEMS_None UMETA(DisplayName = "None"),
	
	// 处于地面
	EEMS_Ground UMETA(DisplayName = "Ground"),
	// 处于空中
	EEMS_InAir UMETA(DisplayName = "InAir"),
	// 处于攀爬
	EEMS_Mantle UMETA(DisplayName="Mantle"),
	// 处于布娃娃
	EEMS_Ragdoll UMETA(DisplayName="Ragdoll"),
	
};

USTRUCT(BlueprintType)
struct FEnemyAttackAbilityInfoBase : public FCharacterAttackAbilityInfo
{
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType)
struct FEnemyOnHitAbilityInfoBase : public FCharacterOnHitAbilityInfo
{
	GENERATED_BODY()
	
	
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ADVANCEDLOCOMOTIONSYSTEMV_API UDataAsset_EnemyBase : public UDataAsset_Base
{
	GENERATED_BODY()
public:
	
};
