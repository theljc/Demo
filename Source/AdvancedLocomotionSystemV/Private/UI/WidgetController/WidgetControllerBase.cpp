


#include "UI/WidgetController/WidgetControllerBase.h"

#include "GameplayEffectExtension.h"
#include "AbilitySystem/DemoAbilitySystemComponent.h"
#include "AbilitySystem/AttributeSet/AttributeSetBase.h"
#include "AbilitySystem/Data/AbilityInfo.h"

void UWidgetControllerBase::SetWidgetControllerClass(const FWidgetControllerBaseParam& WidgetControllerClassParam)
{
	PlayerController = WidgetControllerClassParam.PlayerController;
	PlayerState = WidgetControllerClassParam.PlayerState;
	AbilitySystemComponent = WidgetControllerClassParam.AbilitySystemComponent;
	AttributeSet = WidgetControllerClassParam.AttributeSet;
}

void UWidgetControllerBase::BroadCastInitialValues()
{
	// 绑定的委托将获取并广播当前生命和最大生命
	const UAttributeSetBase* AuraAttributeSet = CastChecked<UAttributeSetBase>(AttributeSet);
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnResilienceChanged.Broadcast(AuraAttributeSet->GetResilience());
	OnMaxResilienceChanged.Broadcast(AuraAttributeSet->GetMaxResilience());
}

void UWidgetControllerBase::BindCallBacksDependencies()
{
	const UAttributeSetBase* AttributeSetBase = CastChecked<UAttributeSetBase>(AttributeSet);
	
	// APlayerStateBase* AuraPlayerState = CastChecked<APlayerStateBase>(PlayerState);
	// AuraPlayerState->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);
	// AuraPlayerState->OnLevelChangedDelegate.AddLambda([this](int32 NewLevel)
	// {
	// 	OnPlayerLevelChanged.Broadcast(NewLevel);
	// });
	
	// 绑定 lambda 回调函数在属性值变化的时候发出通知
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetResilienceAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnResilienceChanged.Broadcast(Data.NewValue);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxResilienceAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
		{
			OnMaxResilienceChanged.Broadcast(Data.NewValue);
		}
	);
	
	if (UDemoAbilitySystemComponent* DemoASC = Cast<UDemoAbilitySystemComponent>(AbilitySystemComponent))
	{
		if (DemoASC->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilities(DemoASC);
		}
		else
		{
			DemoASC->AbilitiesGivenDelegate.AddUObject(this, &UWidgetControllerBase::OnInitializeStartupAbilities);
		}

		// 用 lambda 函数绑定委托
		// DemoASC->EffectAssetTags.AddLambda(
		// 	[this](const FGameplayTagContainer& TagContainer)
		// 	{
		// 		for (FGameplayTag Tag : TagContainer)
		// 		{
		// 			FGameplayTag Message = FGameplayTag::RequestGameplayTag("Message");
		// 			if (Tag.MatchesTag(Message))
		// 			{
		// 				const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
		// 				if (Row != nullptr)
		// 				{
		// 					MessageWidgetRow.Broadcast(*Row);
		// 				}
		// 			}
		// 		}
		// 	}
		// );
	}
}

void UWidgetControllerBase::CallPotionNumChanged(int32 PotionNum)
{
	OnPotionNumChanged.Broadcast(PotionNum);
}

void UWidgetControllerBase::OnInitializeStartupAbilities(UDemoAbilitySystemComponent* DemoASC)
{
	// 当技能还没有被给予时不能初始化
	if (!DemoASC->bStartupAbilitiesGiven) return;

	FForEachAbilities BroadCastDelegate;
	BroadCastDelegate.BindLambda([this, DemoASC](const FGameplayAbilitySpec& AbilitySpec)
	{
		FDemoAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(DemoASC->GetAbilityTagFromSpec(AbilitySpec));
		AbilityInfoDelegate.Broadcast(Info);
	});
	
}
