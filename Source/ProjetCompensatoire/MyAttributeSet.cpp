// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttributeSet.h"
#include"GameplayEffectExtension.h"
#include "ProjetCompensatoireCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
    // Remember to call the parent's implementation.
    Super::PostGameplayEffectExecute(Data);

    // Check to see if this call affects our Health by using the Property Getter.
    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        // This Gameplay Effect is changing Health. Apply it, but restrict the value first.
        // In this case, Health's base value must be non-negative.
        SetHealth(FMath::Max(GetHealth(), 0.0f));
        
    }

    if (Data.EvaluatedData.Attribute == GetManaAttribute())
    {
       
        SetMana(FMath::Max(GetMana(), 0.0f));
    }

    if (Data.EvaluatedData.Attribute == GetSpeedAttribute())
    {
       
        SetSpeed(FMath::Max(GetSpeed(), 0.0f));

        if (AActor* OwningActor = GetOwningActor())
        {
            if (AProjetCompensatoireCharacter* Character = Cast<AProjetCompensatoireCharacter>(OwningActor))
            {
                if (Character->GetCharacterMovement())
                {
                    Character->GetCharacterMovement()->MaxWalkSpeed = GetSpeed();
                }
            }
        }


    }

   

    if (Data.EvaluatedData.Attribute == GetbaseSpeedAttribute())
    {

        SetSpeed(FMath::Max(GetbaseSpeed(), 0.0f));

        if (AActor* OwningActor = GetOwningActor())
        {
            if (AProjetCompensatoireCharacter* Character = Cast<AProjetCompensatoireCharacter>(OwningActor))
            {
                if (Character->GetCharacterMovement())
                {
                    Character->GetCharacterMovement()->MaxWalkSpeed = GetbaseSpeed();
                }
            }
        }


    }
}