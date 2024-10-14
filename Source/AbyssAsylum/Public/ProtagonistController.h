// Fill out your copyright notice in the Description page of Project Settings.


#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, text)

#pragma once

#include "CoreMinimal.h"
#include "ProtagonistController.generated.h"

class AProtagonist;
class UEnhancedInputComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionInstance;

/**
 * 
 */
UCLASS(Abstract)
class ABYSSASYLUM_API AProtagonistController : public APlayerController
{
protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

private:
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Controls")
	UInputMappingContext* InputMappingContext = nullptr;
	// TObjectPtr<UInputMappingContext> InputMappingPtr = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Controls")
	UInputAction* ActionMove = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Controls")
	UInputAction* ActionDash = nullptr;

private:
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	UPROPERTY()
	AProtagonist* Protagonist = nullptr;

	const float MaxSpeed = 256.0f;
	const float DashSpeed = MaxSpeed * 3.5f;
	const FVector PositiveX = FVector(1, 0, 0);
	const FVector PositiveY = FVector(0, 1, 0);

	const float DashDuration = 0.2f;
	const float DashCooldown = 1.5f;
	bool dashing = false;
	float DashTimer = 0.0f;
	float DashCooldownTimer = 0.0f;
	FVector DashDirection = FVector(0, 0, 0);

protected:
	void MoveCallback(const FInputActionInstance& Instance);
	void MoveCleanUp(const FInputActionInstance& Instance);

	void DashCallback(const FInputActionInstance& Instance);

	virtual void Tick(float DeltaSeconds) override;
};