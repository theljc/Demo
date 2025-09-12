


#include "Player/PlayerControllerBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/DemoAbilitySystemComponent.h"

APlayerControllerBase::APlayerControllerBase()
{
	
}

void APlayerControllerBase::PlayerTick(const float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
}

void APlayerControllerBase::ClientSetHUD_Implementation(TSubclassOf<AHUD> NewHUDClass)
{
	Super::ClientSetHUD_Implementation(NewHUDClass);
	
}

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	
	bReplicates = true;
	check(DemoContext);

	// 获得输入子系统
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer());

	// 多人游戏时服务器上会有所有的 PlayerController，所以不能用 check 检查，需要用 if 判断
	if (InputSubsystem)
	{
		// 添加输入映射
		InputSubsystem->AddMappingContext(DemoContext, 0);
	}


	// 显示鼠标
	// bShowMouseCursor = true;
	// 光标类型
	// DefaultMouseCursor = EMouseCursor::Type::Default;

	// FInputModeGameAndUI InputModeData;
	// InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	// 当鼠标光标被捕获到视口中时不隐藏
	// InputModeData.SetHideCursorDuringCapture(false);
	// 设置初始输入模式
	// SetInputMode(InputModeData);
	
}

void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	// UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	// // 绑定 Move 行为
	// EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerControllerBase::Move);
	
}

void APlayerControllerBase::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	// 获得控制器 Yaw 轴方向
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);

	// 获得向前和向右方向的向量
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// 获得控制器所控制的 Pawn
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		// 添加移动输入
		ControlledPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
	
}

UDemoAbilitySystemComponent* APlayerControllerBase::GetASC()
{
	if (AbilitySystemComponent == nullptr)
	{
		AbilitySystemComponent = Cast<UDemoAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}
	return AbilitySystemComponent;
}
