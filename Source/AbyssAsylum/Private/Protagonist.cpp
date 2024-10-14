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
