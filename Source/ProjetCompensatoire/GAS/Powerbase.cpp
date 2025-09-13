// Fill out your copyright notice in the Description page of Project Settings.


#include "../GAS/Powerbase.h"
#include "../ProjetCompensatoireCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"


bool UPowerbase::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
    return true;
}

void UPowerbase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    AProjetCompensatoireCharacter* Player = Cast<AProjetCompensatoireCharacter>(GetAvatarActorFromActorInfo());
    if (Player && niagara)
    {
        UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            niagara,
            Player->spawnloc
        );

        GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Cyan, TEXT("Attempt to cast electricity"));
        if (NiagaraComp)
        {
            NiagaraComp->SetVariableVec3(TEXT("User.end"), Player->VFXtarget);
        }
    }
    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);

}

void UPowerbase::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UPowerbase::ApplyCost(const FGameplayAbilityActorInfo* ActorInfo)
{
}

void UPowerbase::ApplyCooldown(const FGameplayAbilityActorInfo* ActorInfo)
{
}
