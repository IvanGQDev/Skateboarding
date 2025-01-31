// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "SkateBoarding/ScoreSystem/Widgets/ScoreUserWidget.h"
#include "CustomPlayerController.generated.h"


class UInputMappingContext;
class UInputComponent;
class UInputAction;
struct FInputActionValue;

class UWBP_ScoreWidget;

/**
 * 
 */
UCLASS()
class SKATEBOARDING_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PushingAction;

	UPROPERTY(BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool bCanPush = true;
	bool bIsPushing = false;

	FTimerHandle PushCooldownTimer;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float PushCooldown = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InputContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	ACharacter* ControlledCharacter;

	UPROPERTY(EditAnywhere, Category = Movement, meta=(AllowPrivateAccess = "true"))
	float PushSpeed;
	
	UPROPERTY(EditAnywhere, Category = Movement, meta=(AllowPrivateAccess = "true"))
	float NormalSpeed;

	FVector2D CurrentMovementVector = FVector2D::ZeroVector;

	float CurrentSpeed;
	int32 MoveDirection;

	UPROPERTY(EditAnywhere, Category = Movement)
	float MaxSpeed = 800.0f;

	UPROPERTY(EditAnywhere, Category = Movement)
	float AccelerationRate = 800.0f;

	UPROPERTY(EditAnywhere, Category = Movement)
	float DecelerationRate = 400.0f;
	
	UPROPERTY(EditAnywhere, Category = Movement)
    float ManualDecelerationRate = 400.0f;
	

	UPROPERTY(EditAnywhere, Category = Movement)
	float RotationSpeed = 100.0f;

	

	//Widget Logic
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UScoreUserWidget> ScoreWidgetClass;

	UPROPERTY()
	UScoreUserWidget* ScoreWidget;
	
	UFUNCTION()
	void ResetPush();

	
protected:
	void Move(const FInputActionValue& Value);
	void StopMoving();
	void Look(const FInputActionValue& Value);
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;

public:
	void StartPushing(bool Pushing);
	void StopPushing(bool Pushing);
	void NewSpeed(float Speed);
	void StartJumping(bool Jumping);
	void StopJumping(bool Jumping);


	
};
