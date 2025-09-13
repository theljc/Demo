


#include "Character/PlayerCharacter.h"

// #include "BlueprintEditorModule.h"
#include "AbilitySystem/DemoAbilitySystemComponent.h"
// #include "AbilitySystem/DemoAbilitySystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
// #include "GameFramework/GameModeBase.h"
// #include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
// #include "Kismet2/KismetEditorUtilities.h"
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
	
	// 初始化 ActorInfo
	InitAbilityActorInfo();
	
	// if(PlayerStateBase->PlayerStateEnum != EPlayerStateEnum::EPS_Dead && PlayerStateBase->PlayerStateEnum != EPlayerStateEnum::EPS_Possession)
	// {
		// 激活初始 GA
		// AddCharacterAbilities();
	// }
	
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

void APlayerCharacter::Test_CallBPFunction()
{
	// UClass * BlueprintGenClass = LoadClass<AActor>(nullptr, TEXT("Blueprint'/Game/Demo/Test_InterpToMovement.Test_InterpToMovement_C'"));      //获取蓝图中的生成类
	// if (BlueprintGenClass)
	// {
	// 	UBlueprint* Blueprint = UBlueprint::GetBlueprintFromClass(BlueprintGenClass);
	// 	UObject* Instance = NewObject<UObject>(GetTransientPackage(),Blueprint->GeneratedClass);            //根据类来创建对象实例
	//
	// 	// UFunction* Func = Blueprint->GeneratedClass->FindFunctionByName("Pri");     // 在类反射数据中查找名称为[FuncName]的函数
	// 	// Instance->ProcessEvent(Func, nullptr);                                           // 调用蓝图中定义的函数
	//
	// 	FProperty* Prop = FindFProperty<FProperty>(Blueprint->GeneratedClass, "TestInt");// 在类反射数据中查找名称为[IntProp]的属性
	// 	int value = 0;
	// 	Prop->GetValue_InContainer(Instance,&value);        //获取属性
	// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(value).Append("TTT"));
	// }
	
}

void APlayerCharacter::Test_CreateBP()
{
	// UClass* ParentClass = NewObject<UClass>();      // 创建ParentClass
	// ParentClass->SetSuperStruct(UObject::StaticClass()); // 设置父类
	// // 设置类标识
	// ParentClass->ClassFlags = CLASS_Abstract | CLASS_MatchedSerializers | CLASS_Native | CLASS_ReplicationDataIsSetUp | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_HasInstancedReference  | CLASS_Constructed;
	//
	// // 为Class添加事件函数
	// UFunction* BPEvent = NewObject<UFunction>(ParentClass, "BlueprintEvent", RF_Public | RF_Transient);
	// BPEvent->FunctionFlags = FUNC_Public | FUNC_Event | FUNC_BlueprintEvent;
	// BPEvent->Bind();
	// BPEvent->StaticLink(true);
	//
	// BPEvent->Next = ParentClass->Children;              //将函数添加到Parent的Field中
	// ParentClass->Children = BPEvent;
	// ParentClass->AddFunctionToFunctionMap(BPEvent, "BlueprintEvent");
	//
	// ParentClass->Bind();
	// ParentClass->StaticLink(true);
	// ParentClass->AssembleReferenceTokenStream(true);
	//
	// UBlueprint* NewBP = FKismetEditorUtilities::CreateBlueprint(                        //创建蓝图
	// 	ParentClass,
	// 	GetTransientPackage(),
	// 	"NewBP",
	// 	EBlueprintType::BPTYPE_Normal,
	// 	UBlueprint::StaticClass(),
	// 	UBlueprintGeneratedClass::StaticClass());
	//
	// int32 NodePositionY = 0;
	//
	// //在图表中创建事件节点
	// FKismetEditorUtilities::AddDefaultEventNode(NewBP, NewBP->UbergraphPages[0], "BlueprintEvent", ParentClass, NodePositionY); 
	//
	// //当事件不存在时会创建自定义事件
	// FKismetEditorUtilities::AddDefaultEventNode(NewBP, NewBP->UbergraphPages[0], "CustomEvent", ParentClass, NodePositionY);    
	//
	// //打开蓝图编辑器
	// FBlueprintEditorModule& BlueprintEditorModule = FModuleManager::LoadModuleChecked<FBlueprintEditorModule>("Kismet");
	// BlueprintEditorModule.CreateBlueprintEditor(EToolkitMode::Standalone, nullptr, NewBP);
	
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (Controller)
	{
		
		APlayerStateBase* PlayerStateBase = Cast<APlayerStateBase>(Controller->PlayerState);
		
		check(PlayerStateBase);
		
		if(PlayerStateBase->PlayerStateEnum != EPlayerStateEnum::EPS_Dead && PlayerStateBase->PlayerStateEnum != EPlayerStateEnum::EPS_Possession)
		{
			// 激活初始 GA
			AddCharacterAbilities();
		}
	}
	
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

	// 从死亡和附身状态恢复时不执行
	if (PlayerStateBase->PlayerStateEnum != EPlayerStateEnum::EPS_Dead && PlayerStateBase->PlayerStateEnum != EPlayerStateEnum::EPS_Possession)
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
		// 初始化已经在蓝图中做了
		// InitializeDefaultAttributes();
	}
	else
	{
		PlayerStateBase->PlayerStateEnum = EPlayerStateEnum::EPS_Idle;
	}


}
