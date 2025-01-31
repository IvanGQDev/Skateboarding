// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterScoringObject.h"

#include "Components/BoxComponent.h"
#include "SkateBoarding/Character/CustomPlayerState.h"
#include "SkateBoarding/Character/SkaterCharacter.h"

// Sets default values
AMasterScoringObject::AMasterScoringObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(StaticMeshComponent);
	
	CollisionBox->SetBoxExtent(FVector(50, 50, 20));
	CollisionBox->SetRelativeLocation(FVector(0.f, 0.f, 100.f));

	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Overlap);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMasterScoringObject::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AMasterScoringObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMasterScoringObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMasterScoringObject::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
								 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
								 bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this) return;

	
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		// Obtener el PlayerState del Character
		APlayerState* PlayerState = Character->GetPlayerState();
		if (PlayerState)
		{
			if (ACustomPlayerState* SkaterState = Cast<ACustomPlayerState>(PlayerState))
			{
				SkaterState->AddScore(GivenPoints); 
			}
		}
	}
}

