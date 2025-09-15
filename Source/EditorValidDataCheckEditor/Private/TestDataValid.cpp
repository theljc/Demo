// 


#include "TestDataValid.h"

#include "Data/DataAsset_Player.h"

bool UTestDataValid::CanValidateAsset_Implementation(UObject* InAsset) const
{
	// 验证 DataTable
	UDataTable* DataTableAsset = Cast<UDataTable>(InAsset);
	if (!DataTableAsset)
	{
		return false;
	}

	// 获得 DataTable 的结构体名称
	FString RowStructName = DataTableAsset->GetRowStructPathName().ToString();

	// 判断 DataTble 是否由 TableRow_Player 结构体组成
	return RowStructName.Contains(TEXT("TableRow_Player"));
}

EDataValidationResult UTestDataValid::ValidateLoadedAsset_Implementation(UObject* InAsset,
	TArray<FText>& ValidationErrors)
{
	// CanValidateAsset 通过后会执行此函数来验证
	UDataTable* DataTableAsset = Cast<UDataTable>(InAsset);
	
	TArray<FTableRow_Player*> Rows;
	// 获得所有行
	DataTableAsset->GetAllRows<FTableRow_Player>(TEXT("GetDataTableRows"), Rows);
	for (FTableRow_Player* Row : Rows)
	{
		// 验证逻辑：判断 DA_Player 是否为空
		if (!Row->DA_Player)
		{
			// 验证失败时添加错误信息
			AssetFails(InAsset, FText::FromString(TEXT("DA_Player 为空")), ValidationErrors);
		}
	}
	
	return GetValidationResult();
}
