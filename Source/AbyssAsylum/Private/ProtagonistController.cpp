// Fill out your copyright notice in the Description page of Project Settings.

#include "ProtagonistController.h"
#include "Protagonist.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Kismet/KismetSystemLibrary.h"
#include <EnhancedInputSubsystems.h>
#include "InputAction.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	{
		EnhancedInputComponent->BindAction(ActionMove,
			ETriggerEvent::Triggered, this, &AProtagonistController::MoveCallback);
		EnhancedInputComponent->BindAction(ActionMove,
				ETriggerEvent::Completed, this, &AProtagonistController::MoveCleanUp);
	}
	if (ActionDash)
    {
        EnhancedInputComponent->BindAction(ActionDash,
            ETriggerEvent::Started, this, &AProtagonistController::DashCallback);
    }
}

void AProtagonistController::OnUnPossess()
{
	EnhancedInputComponent->ClearActionBindings();
	
	Super::OnUnPossess();
}

void AProtagonistController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (DashTimer > 0.0f)
	{
		FVector DashVector = DashDirection * DashSpeed;
		Protagonist->GetCharacterMovement()->MoveSmooth(DashVector, DeltaTime);
		DashTimer -= DeltaTime;
	} else {
		dashing = false;
	}

	if (DashCooldownTimer > 0.0f)
		DashCooldownTimer -= DeltaTime;
}

void AProtagonistController::MoveCallback(const FInputActionInstance& Instance)
{
	if (dashing)
		return;
	
	FVector2D InputValue = Instance.GetValue().Get<FVector2D>();

	Protagonist->Facing = Protagonist->Vec2ToFaceDirection(InputValue);
	
	InputValue.Normalize();
	print(InputValue.ToString());
	
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	float DistToMove = MaxSpeed * DeltaTime;
	// InputValue *= DistToMove;
	InputValue *= MaxSpeed;
	
	// Use X and Y for your logic
	const float X = InputValue.X;
	const float Y = InputValue.Y;

	if (Protagonist)
	{
		// Protagonist->AddMovementInput(PositiveX, X);
		// Protagonist->AddMovementInput(PositiveY, Y);
		FVector MovementVector = FVector(X, Y, 0.0f);
		Protagonist->GetCharacterMovement()->MoveSmooth(MovementVector, DeltaTime);
	}

	Protagonist->Velocity = InputValue.Size();
}

void AProtagonistController::MoveCleanUp(const FInputActionInstance& Instance)
{
	Protagonist->Velocity = 0.0f;
}

void AProtagonistController::DashCallback(const FInputActionInstance& Instance)
{
	if (dashing)
		return;
	
	if (DashTimer <= 0.0f)
	{
		dashing = true;
		DashTimer = DashDuration;
		DashCooldownTimer = DashCooldown;
		FVector2D DashDirection2D = Protagonist->FaceDirectionToVec2(Protagonist->Facing);
		DashDirection2D.Normalize();
		DashDirection = FVector(DashDirection2D.X, DashDirection2D.Y, 0.0f);
	}
}