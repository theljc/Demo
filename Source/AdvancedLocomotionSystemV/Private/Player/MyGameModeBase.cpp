


#include "Player/MyGameModeBase.h"

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->SpawnActor()
}

void AMyGameModeBase::TravelToNewMap(const FString& MapPath)
{
	if (MapPath.IsEmpty()) return;
	
	if (UWorld* World = GetWorld())
	{
		World->SeamlessTravel(MapPath);
	}
}
