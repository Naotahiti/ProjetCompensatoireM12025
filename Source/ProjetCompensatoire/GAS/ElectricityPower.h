// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GAS/Powerbase.h"
#include "ElectricityPower.generated.h"

/**
 * 
 */
UCLASS()
class PROJETCOMPENSATOIRE_API UElectricityPower : public UPowerbase
{
	GENERATED_BODY()

public:
    UElectricityPower()
    {
        AbilityName = "Electricity";
        ManaCost = 20.f;
        Cooldown = 2.f;
        ElementType = "Electricity";
        /*CooldownTag = FGameplayTag::RequestGameplayTag(FName("Ability.Cooldown.Fireball"));*/
    }

    virtual void ActivateAbility(
        const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayAbilityActivationInfo ActivationInfo,
        const FGameplayEventData* TriggerEventData
    ) override
    {
        if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
        {
            EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
            return;
        }

        // Logique Fireball (spawn projectile par ex.)
        UE_LOG(LogTemp, Warning, TEXT("🔥 Fireball lancée !"));

        EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
    }
	
};
