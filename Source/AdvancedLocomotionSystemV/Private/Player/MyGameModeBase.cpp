


#include "Player/MyGameModeBase.h"

#include "Player/PlayerControllerBase.h"

AMyGameModeBase::AMyGameModeBase()
{
	PlayerControllerClass = APlayerControllerBase::StaticClass();
}

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
