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

USTRUCT(BlueprintType)
struct FEnemyAttackAbilityInfoBase
{
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType)
struct FEnemyOnHitAbilityInfoBase
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
