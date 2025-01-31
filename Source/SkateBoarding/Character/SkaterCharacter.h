// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SkaterCharacter.generated.h"

class UInputMappingContext;
class UInputComponent;
class UInputAction;
struct FInputActionValue;

UCLASS()
class SKATEBOARDING_API ASkaterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASkaterCharacter();

protected:
	virtual void BeginPlay() override;


public:	
	virtual void Tick(float DeltaTime) override;

private:
	
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = "Components")
	TSubclassOf<AActor> SkateboardClass;
	AActor* SkateboardActor;
	
};
