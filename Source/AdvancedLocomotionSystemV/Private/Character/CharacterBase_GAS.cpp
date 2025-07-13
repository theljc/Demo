#include "Character/CharacterBase_GAS.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/DemoAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"


bool ACharacterBase_GAS::GetCooldownRemainingForTag(FGameplayTagContainer CooldownTags, float& TimeRemaining, float& CooldownDuration)
{
	if (AbilitySystemComponent && CooldownTags.Num() > 0)
	{
		TimeRemaining = 0.f;
		CooldownDuration = 0.f;

		FGameplayEffectQuery const Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(CooldownTags);
		TArray< TPair<float, float> > DurationAndTimeRemaining = AbilitySystemComponent->GetActiveEffectsTimeRemainingAndDuration(Query);
		if (DurationAndTimeRemaining.Num() > 0)
		{
			int32 BestIdx = 0;
			float LongestTime = DurationAndTimeRemaining[0].Key;
			for (int32 Idx = 1; Idx < DurationAndTimeRemaining.Num(); ++Idx)
			{
				if (DurationAndTimeRemaining[Idx].Key > LongestTime)
				{
					LongestTime = DurationAndTimeRemaining[Idx].Key;
					BestIdx = Idx;
				}
			}

			TimeRemaining = DurationAndTimeRemaining[BestIdx].Key;
			CooldownDuration = DurationAndTimeRemaining[BestIdx].Value;

			return true;
		}
	}
	return false;
}

// Sets default values
ACharacterBase_GAS::ACharacterBase_GAS()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	// GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetMesh()->SetIsReplicated(true);
	
	// FName 类型不需要加 TEXT 宏
	// Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	// Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	// Weapon->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	// Weapon->SetIsReplicated(true);
	
}

UAbilitySystemComponent* ACharacterBase_GAS::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

float ACharacterBase_GAS::CalculateSpeed()
{
	FVector Velocity = GetVelocity();
	Velocity.Z = 0.f;
	return Velocity.Size();
}

// Called when the game starts or when spawned
void ACharacterBase_GAS::BeginPlay()
{
	Super::BeginPlay();
	
    // if (AbilitySystemComponent != nullptr)
    // {
    //     if (PreloadedAbilities.Num() > 0)
    //     {
    //         for (auto i = 0; i < PreloadedAbilities.Num(); i++)
    //         {
    //             if (PreloadedAbilities[i] != nullptr)
    //             {
    //                 AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(PreloadedAbilities[i].GetDefaultObject(), 1, 0));
    //             }
    //         }
    //
    //     }
    //
    //     AbilitySystemComponent->InitAbilityActorInfo(this, this);
    // }
}

void ACharacterBase_GAS::InitAbilityActorInfo()
{
	
}

void ACharacterBase_GAS::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> DefaultGameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(DefaultGameplayEffectClass);

	// 应用 GE
	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultGameplayEffectClass, Level, EffectContextHandle);
	FActiveGameplayEffectHandle test = GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), GetAbilitySystemComponent());
	if (!test.WasSuccessfullyApplied())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, DefaultGameplayEffectClass->GetName() + FString(TEXT(" 失败")));
		
	}
	
}

void ACharacterBase_GAS::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultStartUpGameplayEffectClass, 1.f);
}

void ACharacterBase_GAS::AddCharacterAbilities() const
{
	if (!HasAuthority())
	{
		return;
	}
	UDemoAbilitySystemComponent* DemoASC = Cast<UDemoAbilitySystemComponent>(AbilitySystemComponent);
	
	DemoASC->AddCharacterAbilities(PreloadedAbilities);
	DemoASC->AddCharacterPassiveAbilities(StartUpPassiveAbilities);
}

// Called every frame
void ACharacterBase_GAS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase_GAS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterBase_GAS::PrintStr() {
	TArray<UObject*> uclass_arr;
	GetObjectsOfClass(UClass::StaticClass(), uclass_arr);
	int count = 0;
	for (auto i : uclass_arr) {
		count++;
	}
	FString test_str = FString::Printf(TEXT("%d"), count);
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, test_str);
}

