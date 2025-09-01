// 


#include "Player/GameInstanceBase.h"

void UGameInstanceBase::PreLoadMap()
{
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UGameInstanceBase::PostLoadMap);
	
}

void UGameInstanceBase::PostLoadMap(UWorld* NewWorld)
{
	OnMapLoad.Broadcast(NewWorld);
}
