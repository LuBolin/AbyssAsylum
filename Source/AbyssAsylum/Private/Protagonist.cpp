// Fill out your copyright notice in the Description page of Project Settings.


#include "Protagonist.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"

AProtagonist::AProtagonist()
{
	PrimaryActorTick.bCanEverTick = true;
	
	InitCamera();
}

void AProtagonist::InitCamera()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->TargetArmLength = 200.0f;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = 1.0f;

	// orthographic camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	CameraComponent->OrthoWidth = 960.0f;
	CameraComponent->AspectRatio = 16.0f / 9.0f;
	CameraComponent->SetOrthoFarClipPlane(1000.0f);
	CameraComponent->SetOrthoNearClipPlane(50.0f);

	SpringArmComponent->SetWorldRotation(FRotator(0.0f, -90.0f, -90.0f));
}

void AProtagonist::BeginPlay()
{
	Super::BeginPlay();

}

void AProtagonist::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProtagonist::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

FaceDirection AProtagonist::Vec2ToFaceDirection(FVector2D Vec2)
{
	if (Vec2.X != 0)
		Vec2.X = Vec2.X / FMath::Abs(Vec2.X);
	if (Vec2.Y != 0)
        Vec2.Y = Vec2.Y / FMath::Abs(Vec2.Y);

	FaceDirection result = FaceDirection::F_DOWN;
    if (Vec2 == FVector2D(0.0f, -1.0f))
        result = FaceDirection::F_UP;
    else if (Vec2 == FVector2D(0.0f, 1.0f))
        result = FaceDirection::F_DOWN;
    else if (Vec2 == FVector2D(-1.0f, 0.0f))
        result = FaceDirection::F_LEFT;
    else if (Vec2 == FVector2D(1.0f, 0.0f))
        result = FaceDirection::F_RIGHT;
    else if (Vec2 == FVector2D(-1.0f, -1.0f))
        result = FaceDirection::F_LEFTUP;
    else if (Vec2 == FVector2D(-1.0f, 1.0f))
        result = FaceDirection::F_LEFTDOWN;
    else if (Vec2 == FVector2D(1.0f, -1.0f))
        result = FaceDirection::F_RIGHTUP;
    else if (Vec2 == FVector2D(1.0f, 1.0f))
        result = FaceDirection::F_RIGHTDOWN;
	return result;
}

FVector2D AProtagonist::FaceDirectionToVec2(FaceDirection FaceDir)
{
	FVector2D result = FVector2D::ZeroVector;
	switch (FaceDir)
    {
		case FaceDirection::F_UP:
            result = FVector2D(0.0f, -1.0f);
            break;
		case FaceDirection::F_DOWN:
            result = FVector2D(0.0f, 1.0f);
            break;
		case FaceDirection::F_LEFT:
            result = FVector2D(-1.0f, 0.0f);
            break;
		case FaceDirection::F_RIGHT:
            result = FVector2D(1.0f, 0.0f);
            break;
		case FaceDirection::F_LEFTUP:
            result = FVector2D(-1.0f, -1.0f);
            break;
		case FaceDirection::F_LEFTDOWN:
            result = FVector2D(-1.0f, 1.0f);
            break;
		case FaceDirection::F_RIGHTUP:
            result = FVector2D(1.0f, -1.0f);
            break;
		case FaceDirection::F_RIGHTDOWN:
            result = FVector2D(1.0f, 1.0f);
            break;
    }
	return result;
}

