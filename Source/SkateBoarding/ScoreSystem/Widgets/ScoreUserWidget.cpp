// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreUserWidget.h"

void UScoreUserWidget::UpdateScore(int32 NewScore)
{
	if (ScoreText)
	{
		ScoreText->SetText(FText::AsNumber(NewScore));
	}
}