// Fill out your copyright notice in the Description page of Project Settings.


#include "SkaterCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASkaterCharacter::ASkaterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ASkaterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (SkateboardClass)
	{
		FVector Location = GetActorLocation() + FVector(0.0f, 0.0f, -100.0f); // Ajusta la posición
		FRotator Rotation = GetActorRotation() + FRotator(0.0f, 90.0f, 0.0f);// Ajusta la rotación
		FActorSpawnParameters SpawnParams;
		SkateboardActor = GetWorld()->SpawnActor<AActor>(SkateboardClass, Location, Rotation, SpawnParams);
		SkateboardActor->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
		SkateboardActor->SetActorEnableCollision(false);
	}
}

// Called every frame
void ASkaterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
