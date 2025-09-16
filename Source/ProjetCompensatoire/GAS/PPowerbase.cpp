// Fill out your copyright notice in the Description page of Project Settings.


#include "../GAS/PPowerbase.h"
#include "../ProjetCompensatoireCharacter.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "../MyAttributeSet.h"

//bool UPPowerbase::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
//{
//    //  if(ManaCost<1)
//    AProjetCompensatoireCharacter* Player = Cast<AProjetCompensatoireCharacter>(ActorInfo->AvatarActor.Get());
//    if (!Player) return false;
//    UAbilitySystemComponent* asc = Player->GetAbilitySystemComponent();
//    float timeelapsed = asc->GetNumericAttribute(UMyAttributeSet::GetManaAttribute());
//    if (Cooldown < timeelapsed)
//        return true;
//    else
//        return false;
//}

void UPPowerbase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    AProjetCompensatoireCharacter* Player = Cast<AProjetCompensatoireCharacter>(GetAvatarActorFromActorInfo());
    if (Player && niagara)
    {
        UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            niagara,
            Player->spawnloc
        );

        // GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Cyan, TEXT("Attempt to cast electricity"));
        if (NiagaraComp)
        {
            NiagaraComp->SetVariableVec3(TEXT("User.end"), Player->VFXtarget);
        }

    }
    CommitAbilityCooldown(Handle,ActorInfo,ActivationInfo,true);
    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);

}

void UPPowerbase::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

//void UPPowerbase::ApplyCost(const FGameplayAbilityActorInfo* ActorInfo)
//{
//}
//
//void UPPowerbase::ApplyCooldown(const FGameplayAbilityActorInfo* ActorInfo)
//{
//}
