// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "PPowerbase.h"
#include "Interactible.generated.h"

UCLASS()
class PROJETCOMPENSATOIRE_API AInteractible : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractible();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GASComponent", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPPowerbase> weakness;

	

};
