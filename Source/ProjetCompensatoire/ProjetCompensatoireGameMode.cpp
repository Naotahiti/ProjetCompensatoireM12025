// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjetCompensatoireGameMode.h"
#include "ProjetCompensatoireCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjetCompensatoireGameMode::AProjetCompensatoireGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
