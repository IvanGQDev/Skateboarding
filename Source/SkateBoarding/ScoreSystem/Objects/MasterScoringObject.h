// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterScoringObject.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class SKATEBOARDING_API AMasterScoringObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterScoringObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, Category = "Points")
	int32 GivenPoints;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
								 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
								 bool bFromSweep, const FHitResult& SweepResult);
};
