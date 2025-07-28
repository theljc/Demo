


#include "Character/EnemyCharacter.h"

#include "DemoGameplayTags.h"
#include "AbilitySystem/DemoAbilitySystemComponent.h"
#include "AbilitySystem/DemoAbilitySystemLibrary.h"
#include "Components/WidgetComponent.h"
#include "Data/DataAsset_Boss.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Widget/MainUserWidget.h"

AEnemyCharacter::AEnemyCharacter()
{
	// 设置默认 Visibility 通道为 block 状态
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UDemoAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UAttributeSetBase>("AttributeSet");
	
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());

	
	// bUseControllerRotationPitch = false;
	// bUseControllerRotationYaw = false;
	// bUseControllerRotationRoll = false;
	//
	// GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (!HasAuthority()) return;
	
	// AuraAIController = Cast<AAuraAIController>(NewController);
	// AuraAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	// AuraAIController->RunBehaviorTree(BehaviorTree);
	// AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	// AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangerAttacker"), CharacterClass != ECharacterClass::Warrior);

}

void AEnemyCharacter::HitReactTagChanged(const FGameplayTag CallBackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	// if (AuraAIController && AuraAIController->GetBlackboardComponent())
	// {
	// 	AuraAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
	// }
}

void AEnemyCharacter::CreateDataInstance()
{
	if (BossDataClass != nullptr)
	{
		BossData = NewObject<UDataAsset_Boss>(this, BossDataClass);
		UE_LOG(LogTemp, Log, TEXT("BossData"))
	}
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	
	InitAbilityActorInfo();
	
	if (HasAuthority())
	{
		// UAuraAbilitySystemLibrary::GiveStartUpAbility(this, AbilitySystemComponent, CharacterClass);
		AddCharacterAbilities();
	}

	UMainUserWidget* MainUserWidget = Cast<UMainUserWidget>(HealthBar->GetUserWidgetObject());
	if (MainUserWidget)
	{
		MainUserWidget->SetWidgetController(this);
	}

	const UAttributeSetBase* ASBase = Cast<UAttributeSetBase>(AttributeSet);
	if (ASBase)
	{
		// 当属性被改变时调用 lambda 函数进行广播
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ASBase->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			});
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ASBase->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			});

		
		// AbilitySystemComponent->RegisterGameplayTagEvent(FDemoGameplayTags::Get().Effect_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
		// 	this,
		// 	&AEnemyCharacter::HitReactTagChanged
		// );

		// 初始广播生命值和最大生命值
		OnHealthChanged.Broadcast(ASBase->GetHealth());
		OnMaxHealthChanged.Broadcast(ASBase->GetMaxHealth());
		
	}
}

void AEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	// 调用 AbilityActorInfoSet 表示 ActorInfo 已经设置好了
	Cast<UDemoAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}
}

void AEnemyCharacter::InitializeDefaultAttributes() const
{
	// 用函数库里的静态函数初始化属性
	// UDemoAbilitySystemLibrary::InitalizeDefaultAttribute(this, CharacterClass, Level, AbilitySystemComponent);
	
}
