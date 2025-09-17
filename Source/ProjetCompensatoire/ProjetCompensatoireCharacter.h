// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AbilitySystemInterface.h"
#include "GAS/PPowerbase.h"
#include "ProjetCompensatoireCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
//class UPowerbase;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AProjetCompensatoireCharacter : public ACharacter , public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SpellAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;
	
public:
	AProjetCompensatoireCharacter();

protected:
	virtual void BeginPlay();

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShiftSpellAction;
	
	UFUNCTION(BlueprintImplementableEvent)
	void addtoskillbar(UTexture2D* texture); // once a new power is picked up , show it to the skill bar with the appropriate image


	UFUNCTION(BlueprintImplementableEvent)
	void highlightskillborder(int i); // visual cue to signal what skill is equiped

	//UFUNCTION()

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void CastSpell();

	void shiftspell();

public:
	UPROPERTY (EditAnywhere , BlueprintReadOnly , Category = "GASComponent" , meta = (AllowPrivateAccess="true"))
	class UAbilitySystemComponent* ASC;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return ASC;
	}

	
	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category ="GASComponent", meta = (AllowPrivateAccess = "true"))
	const class UMyAttributeSet* MyAttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASComponent", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UPPowerbase>> abilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "spell casting effects", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UGameplayEffect>> cast_effect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "electricity effects", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UGameplayEffect>> electricity_effects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "fire effects", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UGameplayEffect>> fire_effects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ice effects", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UGameplayEffect>> ice_effects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TSubclassOf<UPPowerbase> CurrentSpell;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "attributes")
	float damage;

	TArray<FActiveGameplayEffectHandle> PH; // passive handles

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	void receivepower(TSubclassOf<UPPowerbase> power);// add power 

	FVector VFXtarget; // so that VFX particles go towards a target

	FVector spawnloc; // spawn location for VFX

	UFUNCTION(BlueprintCallable)
	float GetMana()const;

	UFUNCTION(BlueprintCallable)
	float GetHealth()const;

	UFUNCTION(BlueprintCallable)
	float GetDamage()const;

	UFUNCTION(BlueprintImplementableEvent)
	void passiveeffects(); // apply effects

	TArray<FGameplayEffectContextHandle> Contexts;
	TArray<FGameplayEffectSpecHandle> SpecHandles;
	TArray<FActiveGameplayEffectHandle> AGEH;

	TArray<TSubclassOf<class UGameplayEffect>> GE;

	// Stocke les effets passifs actifs
	TMap<TSubclassOf<UGameplayAbility>, FActiveGameplayEffectHandle> ActivePassiveEffects;


	void ActivatePassiveEffects(TSubclassOf<UGameplayAbility> AbilityClass, TSubclassOf<UGameplayEffect> PassiveEffect);

	void DeactivatePassiveEffects(TSubclassOf<UGameplayAbility> AbilityClass);

	//UFUNCTION()
	//virtual float TakeDamage
	//(
	//	float DamageAmount,
	//	struct FDamageEvent const& DamageEvent,
	//	class AController* EventInstigator,
	//	AActor* DamageCauser
	//);
	
};

