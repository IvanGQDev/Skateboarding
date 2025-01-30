// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "CustomPlayerController.generated.h"

class UInputMappingContext;
class UInputComponent;
class UInputAction;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class SKATEBOARDING_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PushingAction;

	ACharacter* ControlledCharacter;

	UPROPERTY(EditAnywhere, Category = Speed)
	float PushSpeed;
	
	UPROPERTY(EditAnywhere, Category = Speed)
	float NormalSpeed;

	virtual void BeginPlay() override;
	
protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	//Try
	virtual void SetupInputComponent() override;

private:
	//Try

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InputContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	


public:
	void StartPushing(bool Pushing);
	void StopPushing(bool Pushing);
	void NewSpeed(float Speed);
	void StartJumping(bool Jumping);
	void StopJumping(bool Jumping);


	
};
