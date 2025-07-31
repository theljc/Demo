#include "Player/PlayerStateBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/DemoAbilitySystemComponent.h"
#include "AbilitySystem/DemoAbilitySystemLibrary.h"
#include "AbilitySystem/AttributeSet/AttributeSetBase.h"
#include "UI/WidgetController/WidgetControllerBase.h"

APlayerStateBase::APlayerStateBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UDemoAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UAttributeSetBase>("AttributeSet");

	// 服务器更新频率
	NetUpdateFrequency = 100.f;
}

void APlayerStateBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerStateEnum = EPlayerStateEnum::EPS_Idle;
	
}

void APlayerStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

UAbilitySystemComponent* APlayerStateBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void APlayerStateBase::CalcHealthPotionProps(int32 Level)
{
	check(AbilitySystemComponent)

	HealthPotionProps.PotionNums--;
	HealthPotionProps.PotionMap[Level]--;
	if (HealthPotionProps.PotionMap[Level] == 0)
	{
		HealthPotionProps.PotionMap.Remove(Level);
	}

	UWidgetControllerBase* WidgetControllerBase = UDemoAbilitySystemLibrary::GetWidgetControllerBase(this);
	WidgetControllerBase->OnPotionNumChanged.Broadcast(HealthPotionProps.PotionNums);
}
