// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerState.h"

ACustomPlayerState::ACustomPlayerState()
{
	PlayerScore = 0;
}

void ACustomPlayerState::AddScore(int Points)
{
	PlayerScore += Points;
	OnScoreUpdated.Broadcast(PlayerScore);
	UE_LOG(LogTemp, Warning, TEXT("Nueva puntuación: %d"), PlayerScore);
}

int32 ACustomPlayerState::GetPlayerScore() const
{
	return PlayerScore;
}

