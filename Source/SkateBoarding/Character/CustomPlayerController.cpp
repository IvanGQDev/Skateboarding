// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"

#include "CustomPlayerState.h"
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
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR: ControlledCharacter es nullptr"));
		return;
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
    			Subsystem->AddMappingContext(InputContext, 0);
	}

	//Widget

	if (ScoreWidgetClass)
	{
		ScoreWidget = CreateWidget<UScoreUserWidget>(this, ScoreWidgetClass);
		if (ScoreWidget)
		{
			ScoreWidget->AddToViewport();
		}
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR: ScoreWidget is nullptr"));
	}
	
	ACustomPlayerState* SkaterState = GetPlayerState<ACustomPlayerState>();
	if (SkaterState && ScoreWidget)
	{
		SkaterState->OnScoreUpdated.AddDynamic(ScoreWidget, &UScoreUserWidget::UpdateScore);

		ScoreWidget->UpdateScore(SkaterState->GetPlayerScore());
	}
}

//Character Movement Logic
void ACustomPlayerController::StartPushing(bool Pushing)
{
	if (Pushing)
	{
		if (CurrentSpeed < 1000)
		{
			CurrentSpeed = FMath::Clamp(CurrentSpeed + 400.0f, NormalSpeed, PushSpeed);
		}
	}
}

void ACustomPlayerController::StopPushing(bool Pushing)
{
	if (!Pushing)
	{
		CurrentSpeed = FMath::FInterpTo(CurrentSpeed, NormalSpeed, GetWorld()->GetDeltaSeconds(), 5.0f);
	}
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
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ACustomPlayerController::StopMoving);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACustomPlayerController::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACustomPlayerController::StartJumping, true);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACustomPlayerController::StopJumping, false);
	}
}

/*
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
		}
	}
}
*/

void ACustomPlayerController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (MovementVector.Y > KINDA_SMALL_NUMBER)  //Press W
	{
		MoveDirection = 1;
	}
	else if (MovementVector.Y < -KINDA_SMALL_NUMBER) //Press S
	{
		MoveDirection = -1;
	}
	else // Without Input
	{
		MoveDirection = 0;
	}

	if (MovementVector.X != 0.0f) //Rotation A and D
	{
		AddYawInput(MovementVector.X * RotationSpeed * GetWorld()->GetDeltaSeconds());
	}
}




void ACustomPlayerController::StopMoving()
{
	MoveDirection = 0;
}

void ACustomPlayerController::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	if (GetPawn() != nullptr)
	{
		if (APawn* ControlledPawn = GetPawn())
		{
			ControlledPawn->AddControllerYawInput(LookAxisVector.X);
			ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
		}
	}
}

void ACustomPlayerController::StartJumping(bool Jumping)
{
	if (ControlledCharacter)
	{
		ControlledCharacter->Jump();
	}
}

void ACustomPlayerController::StopJumping(bool Jumping)
{
	if (ControlledCharacter)
	{
		ControlledCharacter->StopJumping();
	}
}

void ACustomPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ACustomPlayerState* SkateState = GetPlayerState<ACustomPlayerState>())
	{
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Yellow, 
			FString::Printf(TEXT("Puntuacion: %i"), SkateState->GetPlayerScore()));
	}
	

	if (!ControlledCharacter) return;

	UCharacterMovementComponent* MovementComponent = ControlledCharacter->GetCharacterMovement();
	if (!MovementComponent) return;

	
	if (MoveDirection == 1) 
	{
		CurrentSpeed = FMath::FInterpTo(CurrentSpeed, MaxSpeed, DeltaTime, AccelerationRate);
	}
	else if (MoveDirection == -1) 
	{
		CurrentSpeed = FMath::FInterpTo(CurrentSpeed, 0.0f, DeltaTime, DecelerationRate);
	}
	else
	{
		CurrentSpeed = FMath::FInterpTo(CurrentSpeed, 0.0f, DeltaTime, DecelerationRate * 0.5f);
	}

	MovementComponent->MaxWalkSpeed = CurrentSpeed;

	if (CurrentSpeed > 10.0f)
	{
		const FRotator Rotation = ControlledCharacter->GetControlRotation();
		const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        
		ControlledCharacter->AddMovementInput(ForwardDirection, 1.0f);
	}
}




