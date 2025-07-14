


#include "Player/MyGameModeBase.h"

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyGameModeBase::TravelToNewMap(const FString& MapPath)
{
	if (MapPath.IsEmpty()) return;
	
	if (UWorld* World = GetWorld())
	{
		World->SeamlessTravel(MapPath);
	}
}
