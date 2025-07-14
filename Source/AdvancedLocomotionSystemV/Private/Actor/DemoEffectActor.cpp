


#include "Actor/DemoEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/DemoAbilitySystemLibrary.h"
#include "Character/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerControllerBase.h"
#include "Player/PlayerStateBase.h"
#include "UI/HUD/MainHUD.h"
#include "UI/WidgetController/MainWidgetController.h"

// Sets default values
ADemoEffectActor::ADemoEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	
}

// Called when the game starts or when spawned
void ADemoEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADemoEffectActor::OnOverlap(AActor* TargetActor)
{
	if (TargetActor->ActorHasTag(FName("ALS_Character")))
	{
		APlayerStateBase* PlayerStateBase = Cast<APlayerStateBase>(UGameplayStatics::GetPlayerState(this, 0));
		// APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(TargetActor);
		
		WidgetControllerBase = UDemoAbilitySystemLibrary::GetWidgetControllerBase(TargetActor);
		
		if (PlayerStateBase->HealthPotionProps.PotionMap.Contains(ActorLevel))
		{
			PlayerStateBase->HealthPotionProps.PotionMap[ActorLevel]++;
		}
		else
		{
			PlayerStateBase->HealthPotionProps.PotionMap.Add(ActorLevel, 1);
		}
		
		const int32 NewNum = ++PlayerStateBase->HealthPotionProps.PotionNums;
		WidgetControllerBase->OnPotionNumChanged.Broadcast(NewNum);

		Destroy();
		// ApplyEffectToTarget(TargetActor, AppliedGameplayEffect);
	}
	
}

void ADemoEffectActor::OnEndOverlap(AActor* TargetActor)
{
	
}

void ADemoEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	// if (TargetActor->ActorHasTag(FName("Enemy"))) return;
	
	// 用蓝图函数库里的函数获得 ASC 组件
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	// ASC 组件可以为 NULL，GameplayEffect 不能为 NULL
	if (TargetASC == nullptr) return;

	// 创建 EffectContextHandle
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	// 设置触发 GE 的源 Object 是自己
	EffectContextHandle.AddSourceObject(this);
	// 创建 GameplayEffectSpecHandle
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
	// 通过 Handle 应用 GE，Handle 中的 Data 是 TSharedPtr<FGameplayEffectSpec>，Get 函数获得 FGameplayEffectSpec 指针再解引用
	const FActiveGameplayEffectHandle ActiveGameplayEffect = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	Destroy();
	
}



