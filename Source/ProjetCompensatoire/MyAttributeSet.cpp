// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttributeSet.h"
#include"GameplayEffectExtension.h"
#include "ProjetCompensatoireCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
    // Remember to call the parent's implementation.
    Super::PostGameplayEffectExecute(Data);




    if (AActor* OwningActor = GetOwningActor())
    {

        // Le caster en Character
        ACharacter* Character = Cast<AProjetCompensatoireCharacter>(OwningActor);
        if (!Character) return;

        // R�cup�rer le CharacterMovementComponent
        UCharacterMovementComponent* MoveComp = Character->GetCharacterMovement();
       
    // Check to see if this call affects our Health by using the Property Getter.
    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        // This Gameplay Effect is changing Health. Apply it, but restrict the value first.
        // In this case, Health's base value must be non-negative.
        SetHealth(FMath::Clamp(GetHealth(), 0, GetMaxHealth()));
        
    }

    if (Data.EvaluatedData.Attribute == GetManaAttribute())
    {
        float newmana = FMath::Clamp(GetMana(), 0, Getmaxmana());
        SetMana(newmana);
    }

 

   

   

    if (Data.EvaluatedData.Attribute == GetbaseSpeedAttribute())
          {
  
        SetbaseSpeed(FMath::Clamp(GetbaseSpeed(), 0, GetMaxSpeed()));
       
                if (Character->GetCharacterMovement())
                {
                    Character->GetCharacterMovement()->MaxWalkSpeed = GetbaseSpeed();
                }
          }
        }


    


}