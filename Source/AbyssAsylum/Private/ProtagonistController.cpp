// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtagonistController.h"
#include "Protagonist.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Kismet/KismetSystemLibrary.h"
#include <EnhancedInputSubsystems.h>
#include "InputAction.h"
#include "InputMappingContext.h"

void AProtagonistController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	Protagonist = Cast<AProtagonist>(aPawn);
	checkf(Protagonist, TEXT("AProtagonistController::OnPossess: Protagonist is nullptr"));

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("AProtagonistController::OnPossess: EnhancedInputComponent is nullptr"));
	EnhancedInputComponent->RegisterComponent();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(InputSubsystem, TEXT("AProtagonistController::OnPossess: InputSubsystem is nullptr"));

	checkf(InputMappingContext, TEXT("AProtagonistController::OnPossess: InputMappingContext is nullptr"));
	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputMappingContext, 0);
	
	if (ActionMove)
		EnhancedInputComponent->BindAction(ActionMove,
			ETriggerEvent::Triggered, this, &AProtagonistController::MoveCallback);
	EnhancedInputComponent->BindAction(ActionMove,
			ETriggerEvent::Completed, this, &AProtagonistController::MoveCleanUp);
}

void AProtagonistController::OnUnPossess()
{
	EnhancedInputComponent->ClearActionBindings();
	
	Super::OnUnPossess();
}

void AProtagonistController::MoveCallback(const FInputActionInstance& Instance)
{
	FVector2D InputValue = Instance.GetValue().Get<FVector2D>();

	if (InputValue == FVector2D(0.0f, -1.0f))
		Protagonist->Facing = FaceDirection::F_UP;
	else if (InputValue == FVector2D(0.0f, 1.0f))
		Protagonist->Facing = FaceDirection::F_DOWN;
	else if (InputValue == FVector2D(-1.0f, 0.0f))
		Protagonist->Facing = FaceDirection::F_LEFT;
	else if (InputValue == FVector2D(1.0f, 0.0f))
		Protagonist->Facing = FaceDirection::F_RIGHT;
	else if (InputValue == FVector2D(-1.0f, -1.0f))
		Protagonist->Facing = FaceDirection::F_LEFTUP;
	else if (InputValue == FVector2D(-1.0f, 1.0f))
		Protagonist->Facing = FaceDirection::F_LEFTDOWN;
	else if (InputValue == FVector2D(1.0f, -1.0f))
		Protagonist->Facing = FaceDirection::F_RIGHTUP;
	else if (InputValue == FVector2D(1.0f, 1.0f))
		Protagonist->Facing = FaceDirection::F_RIGHTDOWN;

	InputValue.Normalize();
	print(InputValue.ToString());
	
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	float DistToMove = MaxSpeed * DeltaTime;
	InputValue *= DistToMove;
	
	// Use X and Y for your logic
	const float X = InputValue.X;
	const float Y = InputValue.Y;

	if (Protagonist)
	{
		Protagonist->AddMovementInput(PositiveX, X);
		Protagonist->AddMovementInput(PositiveY, Y);
	}

	Protagonist->Velocity = InputValue.Size();
}

void AProtagonistController::MoveCleanUp(const FInputActionInstance& Instance)
{
	Protagonist->Velocity = 0.0f;
}