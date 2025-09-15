// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "PPowerbase.generated.h"

/**
 * 
 */
UCLASS()
class PROJETCOMPENSATOIRE_API UPPowerbase : public UGameplayAbility
{
	GENERATED_BODY()


public:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
    FName AbilityName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
    float ManaCost;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
    float Cooldown;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
    FString ElementType;

    /* UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
     FGameplayTag CooldownTag;*/

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
    UNiagaraSystem* niagara;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Passive")
    TSubclassOf<class UGameplayEffect> PassiveEffect;

    FActiveGameplayEffectHandle PassiveEffectHandle; // stock effect passive handle




protected:

    virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
        const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;

    virtual void ActivateAbility(
        const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData
    ) override;


    virtual void EndAbility(
        const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        bool bReplicateEndAbility,
        bool bWasCancelled
    ) override;

    /** Application du coût */
    virtual void ApplyCost(const FGameplayAbilityActorInfo* ActorInfo);

    /** Application du cooldown */
    virtual void ApplyCooldown(const FGameplayAbilityActorInfo* ActorInfo);
	
};
