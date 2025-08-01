


#include "Character/PlayerCharacter.h"

#include "AbilitySystem/DemoAbilitySystemComponent.h"
#include "AbilitySystem/DemoAbilitySystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Player/PlayerControllerBase.h"
#include "Player/PlayerStateBase.h"
#include "UI/HUD/MainHUD.h"

APlayerCharacter::APlayerCharacter()
{
	
}

void APlayerCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerCharacter, ControllerRotation);
	
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsLocallyControlled())
	{
		FRotator CurrentRotation = GetControlRotation();
		Server_SetControllerRotation(CurrentRotation);
		
		FVector TempAcceleration = GetCharacterMovement()->GetCurrentAcceleration();
		Server_SetAcceleration(TempAcceleration);
	}
}

void APlayerCharacter::OnRep_ReplicatedMovement()
{
	Super::OnRep_ReplicatedMovement();

	// SimProxiesTurn();
	
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	APlayerStateBase* PlayerStateBase = GetPlayerState<APlayerStateBase>();
	check(PlayerStateBase);
	
	if(PlayerStateBase->PlayerStateEnum != EPlayerStateEnum::EPS_Possession)
	{
		// 服务器运行时调用
		// 初始化 ActorInfo
		InitAbilityActorInfo();
		// 激活初始 GA
		// AddCharacterAbilities();
	}
	
	APlayerController* PlayerController = Cast<APlayerController>(NewController);
	// 调用蓝图事件
	Blueprint_PossessedBy(PlayerController);
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// 客户端运行时调用
	InitAbilityActorInfo();
	
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		// 调用蓝图事件
		Blueprint_PossessedBy(PlayerController);
	}
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

void APlayerCharacter::Server_SetControllerRotation_Implementation(FRotator NewRotation)
{
	ControllerRotation = NewRotation;
}

// void APlayerCharacter::SimProxiesTurn()
// {
// 	float Speed = CalculateSpeed();
// 	if (Speed > 0.f)
// 	{
// 		TurningInPlace = ETurningInPlace::ETIP_NotTurning;
// 		return;
// 	}
//
// 	ProxyRotationLastFrame = ProxyRotation;
// 	ProxyRotation = GetActorRotation();
// 	ProxyYaw = UKismetMathLibrary::NormalizedDeltaRotator(ProxyRotation, ProxyRotationLastFrame).Yaw;
// }

void APlayerCharacter::Server_SetAcceleration_Implementation(FVector NewAcceleration)
{
	Acceleration_Replicate = NewAcceleration;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AddCharacterAbilities();
	
}

void APlayerCharacter::InitAbilityActorInfo()
{
	APlayerStateBase* PlayerStateBase = GetPlayerState<APlayerStateBase>();
	check(PlayerStateBase);
	
	AbilitySystemComponent = PlayerStateBase->GetAbilitySystemComponent();
	
	AttributeSet = PlayerStateBase->GetAttributeSet();
	
	// 由于 ASC 组件在 PlayerState 上，所以 Owner 是 PlayerState，Avatar 是拥有组件的玩家角色类
	AbilitySystemComponent->InitAbilityActorInfo(PlayerStateBase, this);

	// 调用 AbilityActorInfoSet 表示 ActorInfo 已经设置好了
	Cast<UDemoAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	
	
	if (PlayerStateBase->PlayerStateEnum != EPlayerStateEnum::EPS_Dead)
	{
		APlayerControllerBase* PlayerControllerBase = Cast<APlayerControllerBase>(GetController());
		if (PlayerControllerBase)
		{
			AMainHUD* MainHUD = Cast<AMainHUD>(PlayerControllerBase->GetHUD());
			if (MainHUD)
			{
				MainHUD->InitOverlay(PlayerControllerBase, PlayerStateBase, AbilitySystemComponent, AttributeSet);
			}
		}

		// 用 GE 初始化属性，这里在客户端和服务器上都进行了初始化，实际上可以只在服务器进行，之后复制到客户端
		InitializeDefaultAttributes();
	}
	else
	{
		PlayerStateBase->PlayerStateEnum = EPlayerStateEnum::EPS_Idle;
	}


}
