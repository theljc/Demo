


#include "AbilitySystem/DemoAbilitySystemLibrary.h"

#include "AbilitySystemLog.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerStateBase.h"
#include "UI/HUD/MainHUD.h"

UWidgetControllerBase* UDemoAbilitySystemLibrary::GetWidgetControllerBase(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AMainHUD* AuraHUD = Cast<AMainHUD>(PC->GetHUD()))
		{
			APlayerStateBase* PS = Cast<APlayerStateBase>(PC->PlayerState);
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerBaseParam WidgetControllerParam(PC, PS, ASC, AS);
			return AuraHUD->GetOverlayWidgetController(WidgetControllerParam);
		}
	}
	return nullptr;
}

void UDemoAbilitySystemLibrary::SendGameplayEventToActor_Modify(AActor* Actor, FGameplayTag EventTag,
	FGameplayEventData_Modify Payload)
{
	if (::IsValid(Actor))
	{
		UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent(Actor);
		if (AbilitySystemComponent != nullptr && IsValidChecked(AbilitySystemComponent))
		{
			FScopedPredictionWindow NewScopedWindow(AbilitySystemComponent, true);
			AbilitySystemComponent->HandleGameplayEvent(EventTag, &Payload);
		}
		else
		{
			ABILITY_LOG(Error, TEXT("UAbilitySystemBlueprintLibrary::SendGameplayEventToActor: Invalid ability system component retrieved from Actor %s. EventTag was %s"), *Actor->GetName(), *EventTag.ToString());
		}
	}
}
