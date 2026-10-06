#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Combat/CombatEnums.h"
#include "CombatInputComponent.generated.h"

class AWrestlerCharacter;
class AMatchController;

// Input action structure
USTRUCT(BlueprintType)
struct FCombatInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UInputAction* InputAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECombatInput ActionType = ECombatInput::None;
};

UCLASS()
class WRESTLECITY_API UCombatInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	UCombatInputComponent();

	virtual void SetupPlayerInputComponent(class APlayerController* PlayerController);

	// ---- Input actions ----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputMappingContext* DefaultMappingContext = nullptr;

	// Xbox Controller / Gamepad buttons
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Gamepad")
	class UInputAction* IA_StrikeGamepad = nullptr;  // X button

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Gamepad")
	class UInputAction* IA_GrappleGamepad = nullptr;  // Y button

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Gamepad")
	class UInputAction* IA_WhipGamepad = nullptr;  // A button

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Gamepad")
	class UInputAction* IA_InteractGamepad = nullptr;  // B button

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Gamepad")
	class UInputAction* IA_ReverseStrikeGamepad = nullptr;  // LB (Q for keyboard)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Gamepad")
	class UInputAction* IA_ReverseGrappleGamepad = nullptr;  // RB (R for keyboard)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Gamepad")
	class UInputAction* IA_RunGamepad = nullptr;  // Left Trigger

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Gamepad")
	class UInputAction* IA_PinGamepad = nullptr;  // Down on D-pad

	// Keyboard / Mouse buttons
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Keyboard")
	class UInputAction* IA_StrikeKeyboard = nullptr;  // Left mouse click

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Keyboard")
	class UInputAction* IA_GrappleKeyboard = nullptr;  // F key

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Keyboard")
	class UInputAction* IA_WhipKeyboard = nullptr;  // E key

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Keyboard")
	class UInputAction* IA_InteractKeyboard = nullptr;  // Space

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Keyboard")
	class UInputAction* IA_ReverseStrikeKeyboard = nullptr;  // Q key

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Keyboard")
	class UInputAction* IA_ReverseGrappleKeyboard = nullptr;  // R key

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Keyboard")
	class UInputAction* IA_RunKeyboard = nullptr;  // Shift

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|Keyboard")
	class UInputAction* IA_PinKeyboard = nullptr;  // Down arrow

	// Owner wrestler
	UPROPERTY()
	AWrestlerCharacter* OwnerWrestler = nullptr;

	// Match controller reference
	UPROPERTY()
	AMatchController* MatchController = nullptr;

	// Called when player presses attack button
	UFUNCTION(BlueprintCallable)
	void OnStrikePressed();

	UFUNCTION(BlueprintCallable)
	void OnStrikeReleased();

	// Called when player presses grapple button
	UFUNCTION(BlueprintCallable)
	void OnGrapplePressed();

	UFUNCTION(BlueprintCallable)
	void OnGrappleReleased();

	// Called when player presses whip button
	UFUNCTION(BlueprintCallable)
	void OnWhipPressed();

	UFUNCTION(BlueprintCallable)
	void OnWhipReleased();

	// Called when player presses interact button
	UFUNCTION(BlueprintCallable)
	void OnInteractPressed();

	UFUNCTION(BlueprintCallable)
	void OnInteractReleased();

	// Called when player presses reverse strike button
	UFUNCTION(BlueprintCallable)
	void OnReverseStrikePressed();

	UFUNCTION(BlueprintCallable)
	void OnReverseStrikeReleased();

	// Called when player presses reverse grapple button
	UFUNCTION(BlueprintCallable)
	void OnReverseGrapplePressed();

	UFUNCTION(BlueprintCallable)
	void OnReverseGrappleReleased();

	// Called when player presses run button
	UFUNCTION(BlueprintCallable)
	void OnRunPressed();

	UFUNCTION(BlueprintCallable)
	void OnRunReleased();

	// Called when player presses pin button
	UFUNCTION(BlueprintCallable)
	void OnPinPressed();

	UFUNCTION(BlueprintCallable)
	void OnPinReleased();

	// Master input handler
	UFUNCTION(BlueprintCallable)
	void HandleCombatInput(ECombatInput Input, bool bPressed);

	UFUNCTION(BlueprintCallable)
	void SetupBindings();

	UPROPERTY()
	bool bIsRunning = false;

	UPROPERTY()
	bool bIsReverseWindowOpen = false;
};
