// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
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

	UPROPERTY(BlueprintReadWrite , Category = "attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Mana);

	UPROPERTY(BlueprintReadWrite, Category = "attributes")
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Speed);
	
};
