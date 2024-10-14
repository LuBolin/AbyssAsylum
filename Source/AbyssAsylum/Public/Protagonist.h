// Fill out your copyright notice in the Description page of Project Settings.

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, text)

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "Protagonist.generated.h"

UENUM(BlueprintType)
enum FaceDirection
{
	F_UP		UMETA(DisplayName = "UP"),
	F_DOWN		UMETA(DisplayName = "DOWN"),
	F_LEFT		UMETA(DisplayName = "LEFT"),
	F_RIGHT		UMETA(DisplayName = "RIGHT"),
	F_LEFTUP	UMETA(DisplayName = "LEFTUP"),
	F_LEFTDOWN	UMETA(DisplayName = "LEFTDOWN"),
	F_RIGHTUP	UMETA(DisplayName = "RIGHTUP"),
	F_RIGHTDOWN	UMETA(DisplayName = "RIGHTDOWN")
};

UCLASS()
class ABYSSASYLUM_API AProtagonist : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	AProtagonist();

	UPROPERTY(BlueprintReadOnly, Category = "State")
	TEnumAsByte<FaceDirection> Facing = FaceDirection::F_DOWN;
	UPROPERTY(BlueprintReadOnly, Category = "State")
	float Velocity = 0.0f;

	FaceDirection Vec2ToFaceDirection(FVector2D Vec2);
	FVector2D FaceDirectionToVec2(FaceDirection FaceDir);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* CameraComponent;


private:
	void InitCamera();
};