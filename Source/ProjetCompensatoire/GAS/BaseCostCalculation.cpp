// Fill out your copyright notice in the Description page of Project Settings.


#include "../GAS/BaseCostCalculation.h"
#include "../GAS/PPowerbase.h"




float UBaseCostCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const UPPowerbase* Ability = Cast<UPPowerbase>(Spec.GetContext().GetAbility());
	if (!Ability)
	{
		return 0.f;
	}
	return Ability->Cooldown;//ManaCost;

}