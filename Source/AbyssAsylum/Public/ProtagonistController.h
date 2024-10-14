// Fill out your copyright notice in the Description page of Project Settings.

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

private:
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	UPROPERTY()
	AProtagonist* Protagonist = nullptr;

	const float MaxSpeed = 48.0f;
	const FVector PositiveX = FVector(1, 0, 0);
	const FVector PositiveY = FVector(0, 1, 0);

protected:
	void MoveCallback(const FInputActionInstance& Instance);
	void MoveCleanUp(const FInputActionInstance& Instance);
};