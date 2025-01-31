// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CustomPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreUpdated, int32, NewScore);

UCLASS()
class SKATEBOARDING_API ACustomPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ACustomPlayerState();
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Points);
	
	UFUNCTION(BlueprintCallable, Category = "Score")
	int32 GetPlayerScore() const;
    	
	UPROPERTY(BlueprintAssignable, Category = "Score")
	FOnScoreUpdated OnScoreUpdated;

private:
	UPROPERTY(VisibleAnywhere, Category = "Score")
	int32 PlayerScore;
};
