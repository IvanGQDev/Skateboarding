// Fill out your copyright notice in the Description page of Project Settings.


#include "SkaterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "SkaterCharacter.h"

void USkaterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	SkaterCharacter = Cast<ASkaterCharacter>(TryGetPawnOwner());
}

void USkaterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (SkaterCharacter == nullptr)
	{
		SkaterCharacter = Cast<ASkaterCharacter>(TryGetPawnOwner());
	}
	if (SkaterCharacter == nullptr) return;

	Speed = SkaterCharacter->GetVelocity().Size();

	// Check Moving
	bIsMoving = (Speed > 10.0f);

	// Check Jumping
	bIsJumping = SkaterCharacter->GetCharacterMovement()->IsFalling();

	// Check Movement Direction
	FVector Velocity = SkaterCharacter->GetVelocity();
	FRotator Rotation = SkaterCharacter->GetActorRotation();
	MoveDirection = FMath::RoundToInt(FVector::DotProduct(Velocity.GetSafeNormal(), Rotation.Vector()));

	// Check Pushing
	bIsPushing = SkaterCharacter->GetCharacterMovement()->MaxWalkSpeed > 700;
	

}
