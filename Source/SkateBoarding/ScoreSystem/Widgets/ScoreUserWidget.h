// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ScoreUserWidget.generated.h"


/**
 * 
 */
UCLASS()
class SKATEBOARDING_API UScoreUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ScoreText;

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateScore(int32 NewScore);
};
