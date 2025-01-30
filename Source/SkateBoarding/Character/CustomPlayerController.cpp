// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "SkaterCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


void ACustomPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GetCharacter())
	{
		ControlledCharacter = GetCharacter();
		ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
    			Subsystem->AddMappingContext(InputContext, 0);
	}
}

void ACustomPlayerController::StartPushing(bool Pushing)
{
	NewSpeed(PushSpeed);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Pushing");
}

void ACustomPlayerController::StopPushing(bool Pushing)
{
	NewSpeed(NormalSpeed);
	
}

void ACustomPlayerController::NewSpeed(float Speed)
{
	if (ControlledCharacter->GetCharacterMovement())
	{
		ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed = Speed;
	}
}

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(PushingAction, ETriggerEvent::Started, this, &ACustomPlayerController::StartPushing, true);
		EnhancedInputComponent->BindAction(PushingAction, ETriggerEvent::Completed, this, &ACustomPlayerController::StopPushing, false);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACustomPlayerController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACustomPlayerController::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACustomPlayerController::StartJumping, true);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACustomPlayerController::StopJumping, false);
	}
}
// Try
void ACustomPlayerController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (GetPawn() != nullptr)
	{
		if (APawn* ControlledPawn = GetPawn())
		{
			const FRotator Rotation = ControlledPawn->GetControlRotation();
			const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);

			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
			ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, ControlledPawn->GetName());
		}
	}
}

void ACustomPlayerController::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (GetPawn() != nullptr)
	{
		if (APawn* ControlledPawn = GetPawn())
		{
			// add yaw and pitch input to controller
			ControlledPawn->AddControllerYawInput(LookAxisVector.X);
			ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Looking");
		}
	}
}

void ACustomPlayerController::StartJumping(bool Jumping)
{
	if (ControlledCharacter)
	{
		ControlledCharacter->Jump();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, "Jumping");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Pawn is not a Character!");
	}
}

void ACustomPlayerController::StopJumping(bool Jumping)
{
	if (ControlledCharacter)
	{
		ControlledCharacter->StopJumping();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, "Jumping");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Pawn is not a Character!");
	}
}




