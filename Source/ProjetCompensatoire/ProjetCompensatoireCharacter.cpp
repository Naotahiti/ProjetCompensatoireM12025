// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjetCompensatoireCharacter.h"
#include "ProjetCompensatoireProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyAttributeSet.h" 

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AProjetCompensatoireCharacter

AProjetCompensatoireCharacter::AProjetCompensatoireCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));


}

void AProjetCompensatoireCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (IsValid(ASC))
	{
		MyAttributeSet = ASC->GetSet<UMyAttributeSet>();
		
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void AProjetCompensatoireCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjetCompensatoireCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProjetCompensatoireCharacter::Look);

		//spell casting
		EnhancedInputComponent->BindAction(SpellAction, ETriggerEvent::Started, this, &AProjetCompensatoireCharacter::CastSpell);

		//change equiped spell
		EnhancedInputComponent->BindAction(ShiftSpellAction, ETriggerEvent::Started, this, &AProjetCompensatoireCharacter::shiftspell);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AProjetCompensatoireCharacter::receivepower(TSubclassOf<UGameplayAbility> power)
{
	
	abilities.Add(power);
	ASC->GiveAbility(FGameplayAbilitySpec(power, 1, abilities.Num()-1));
	CurrentSpell = power;
	ASC->InitAbilityActorInfo(this, this);
	highlightskillborder(abilities.Find(CurrentSpell));
}




void AProjetCompensatoireCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AProjetCompensatoireCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AProjetCompensatoireCharacter::CastSpell()
{
	FVector start = FirstPersonCameraComponent->GetComponentLocation();
	FVector end = start+FirstPersonCameraComponent->GetForwardVector()*2000.;

	FCollisionQueryParams Params;
	FHitResult hit;
	Params.AddIgnoredActor(this); // On ignore le joueur

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		hit,
		start,
		end,
		ECC_Visibility,
		Params
	);

	/*DrawDebugLine(GetWorld(), start, hit.Location, FColor::Red, false, 2.f, 0, 2.f);


	DrawDebugPoint(GetWorld(), hit.Location, 10.f, FColor::Blue, false, 2.f);*/

	//if we have at least one power and we can hit something with it

	if (bHit&&abilities.Num() > 0)
	{
	
		VFXtarget = hit.Location;
		spawnloc = start;
		ASC->TryActivateAbilityByClass(CurrentSpell);
		auto a = CurrentSpell->GetFName();
		FString s = a.ToString();
		GEngine->AddOnScreenDebugMessage(-1, 5., FColor::Cyan, s);
	}
	
	else
		GEngine->AddOnScreenDebugMessage(-1, 5., FColor::Cyan, "no power found");
}

void AProjetCompensatoireCharacter::shiftspell() // change de sort à condition d'en avoir au moins 2
{
	if (abilities.IsEmpty())
		return;
	
	if (abilities.Num() -1 > abilities.Find(CurrentSpell))
		{
			CurrentSpell = abilities[abilities.Find(CurrentSpell) + 1];
			auto a = CurrentSpell->GetFName();
			FString s = a.ToString();
			GEngine->AddOnScreenDebugMessage(-1, 5., FColor::Cyan, s);
			highlightskillborder(abilities.Find(CurrentSpell));
		}
		else
		{
			CurrentSpell = abilities[0];
			auto a = CurrentSpell->GetFName();
			FString s = a.ToString();
			GEngine->AddOnScreenDebugMessage(-1, 5., FColor::Cyan, s);
			highlightskillborder(abilities.Find(CurrentSpell));
		}
	
}
