// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MyAttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName,PropertyName)\
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName,PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)\
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class PROJETCOMPENSATOIRE_API UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public: 

	UPROPERTY(BlueprintReadOnly , Category = "attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Mana);
	/*GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UMyAttributeSet, Mana)
		GAMEPLAYATTRIBUTE_VALUE_GETTER(Mana)
		GAMEPLAYATTRIBUTE_VALUE_SETTER(Mana)
		GAMEPLAYATTRIBUTE_VALUE_INITTER(Mana)*/

	UPROPERTY(BlueprintReadOnly, Category = "attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "attributes")
	FGameplayAttributeData maxmana;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, maxmana);

	UPROPERTY(BlueprintReadOnly, Category = "attributes")
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Speed);

	UPROPERTY(BlueprintReadOnly, Category = "attributes")
	FGameplayAttributeData baseSpeed;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, baseSpeed);

	UPROPERTY(BlueprintReadOnly, Category = "attributes")
	FGameplayAttributeData DamageReceived;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, DamageReceived);

	/*GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UMyAttributeSet, Mana);
	float GetMana() const;
	void SetMana(float NewVal);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Mana);*/

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
};
