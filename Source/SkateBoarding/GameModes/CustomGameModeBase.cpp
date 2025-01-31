// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameModeBase.h"
#include "SkateBoarding/Character/CustomPlayerState.h"

ACustomGameModeBase::ACustomGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/_Main/Blueprints/Character/BP_SkaterCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		PlayerStateClass = ACustomPlayerState::StaticClass();
	}
}


