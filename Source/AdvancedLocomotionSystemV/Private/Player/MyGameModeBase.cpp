


#include "Player/MyGameModeBase.h"

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyGameModeBase::TravelTest()
{
	GetWorld()->SeamlessTravel("/Game/Demo/Maps/test");
}
