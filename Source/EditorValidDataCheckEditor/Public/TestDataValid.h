// 

#pragma once

#include "CoreMinimal.h"
#include "EditorValidatorBase.h"

#include "TestDataValid.generated.h"

/**
 * 继承自 UEditorValidatorBase 的类会自动注册
 */
UCLASS()
class EDITORVALIDDATACHECKEDITOR_API UTestDataValid : public UEditorValidatorBase
{
	GENERATED_BODY()
public:
	// 指定要验证的资产
	virtual bool CanValidateAsset_Implementation(UObject* InAsset) const override;
	// 具体的验证逻辑
	virtual EDataValidationResult ValidateLoadedAsset_Implementation(UObject* InAsset, TArray<FText>& ValidationErrors) override;
	
};
