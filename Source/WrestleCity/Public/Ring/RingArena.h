#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Combat/CombatEnums.h"
#include "RingArena.generated.h"

// 2D Ring Arena - Fixed side-view wrestling ring
// Think Fire Pro Wrestling: High angle, chunky sprites, visible crowd
UCLASS()
class WRESTLECITY_API ARingArena : public AActor
{
	GENERATED_BODY()

public:
	ARingArena();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// ---- RING DIMENSIONS (2D Side View) ----
	// The ring is a FLAT stage viewed from the side
	// X axis = left/right (horizontal)
	// Y axis = depth (into the screen)
	// Z axis = up/down (height)

	// Ring canvas width (left rope to right rope)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ring|Dimensions")
	float RingWidth = 2000.0f;

	// Ring canvas depth (front rope to back rope)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ring|Dimensions")
	float RingDepth = 2000.0f;

	// Ring canvas height (mat level)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ring|Dimensions")
	float RingHeight = 100.0f;

	// Apron (outside ring, before floor)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ring|Dimensions")
	float ApronWidth = 300.0f;

	// Floor (outside apron)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ring|Dimensions")
	float FloorWidth = 600.0f;

	// ---- RING GEOMETRY ----
	// Center of the ring
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ring|Geometry")
	FVector RingCenter = FVector(0.0f, 0.0f, RingHeight);

	// ---- ROPE SYSTEM ----
	// The ring has 3 ropes on each side
	// Top rope, middle rope, bottom rope
	// In 2D, they appear as horizontal lines with vertical sag

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ring|Ropes")
	float TopRopeHeight = 250.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ring|Ropes")
	float MiddleRopeHeight = 150.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ring|Ropes")
	float BottomRopeHeight = 50.0f;

	// Rope sag (how much they dip in the middle)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ring|Ropes")
	float RopeSag = 30.0f;

	// ---- RING ZONES ----
	// Standing zone: center of ring
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ring|Zones")
	FVector StandingZoneCenter = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ring|Zones")
	float StandingZoneRadius = 400.0f;

	// Rope zone: near the ropes (left/right boundaries)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ring|Zones")
	float RopeZoneDistance = 800.0f;

	// Corner zone: four corners of the ring
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ring|Zones")
	float CornerRadius = 300.0f;

	// ---- CORNER POSITIONS ----
	// Top-left corner (from camera view)
	FVector CornerTopLeft = FVector(-RingWidth / 2.0f, -RingDepth / 2.0f, 0.0f);

	// Top-right corner
	FVector CornerTopRight = FVector(RingWidth / 2.0f, -RingDepth / 2.0f, 0.0f);

	// Bottom-left corner
	FVector CornerBottomLeft = FVector(-RingWidth / 2.0f, RingDepth / 2.0f, 0.0f);

	// Bottom-right corner
	FVector CornerBottomRight = FVector(RingWidth / 2.0f, RingDepth / 2.0f, 0.0f);

	// Turnbuckle pads (physical pillars at corners)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ring|Props")
	float TurnbuckleRadius = 100.0f;

	// ---- RING PROPS ----
	// Chair at ringside (can be picked up)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ring|Props")
	FVector ChairPosition = FVector(-500.0f, RingDepth / 2.0f + ApronWidth, 0.0f);

	// Weapon stick (can be picked up)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ring|Props")
	FVector StickPosition = FVector(500.0f, RingDepth / 2.0f + ApronWidth, 0.0f);

	// Announce table (cannot pass through)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ring|Props")
	FVector AnnounceTablePosition = FVector(0.0f, RingDepth / 2.0f + ApronWidth + 200.0f, 0.0f);

	// ---- CROWD ----
	// Crowd fills the background (visual only)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ring|Crowd")
	bool bShowCrowd = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ring|Crowd")
	float CrowdDistance = 2000.0f;

	// ---- VISUAL COMPONENTS ----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Visual")
	class USkeletalMeshComponent* RingMesh = nullptr;

	// ---- HELPER FUNCTIONS ----

	// Get the world position of a ring zone
	UFUNCTION(BlueprintCallable)
	FVector GetZonePosition(ECombatPosition Position);

	// Check if a position is in a specific zone
	UFUNCTION(BlueprintCallable)
	bool IsInZone(FVector WorldPos, ECombatPosition Zone);

	// Get the closest zone to a world position
	UFUNCTION(BlueprintCallable)
	ECombatPosition GetClosestZone(FVector WorldPos);

	// Move a wrestler to a zone
	UFUNCTION(BlueprintCallable)
	void MoveWrestlerToZone(class AWrestlerCharacter* Wrestler, ECombatPosition TargetZone);

	// Apply zone-specific physics (rope sag, floor damage, etc)
	UFUNCTION(BlueprintCallable)
	void ApplyZonePhysics(class AWrestlerCharacter* Wrestler, ECombatPosition Zone);

	// Rope rebound logic
	UFUNCTION(BlueprintCallable)
	void ApplyRopeRebound(class AWrestlerCharacter* Wrestler, FVector Direction);

	// Corner post shot logic
	UFUNCTION(BlueprintCallable)
	void ApplyCornerPostShot(class AWrestlerCharacter* Wrestler);

	// Count-out logic for floor
	UFUNCTION(BlueprintCallable)
	void ApplyCountOut(class AWrestlerCharacter* Wrestler, float& CountTimer);

	// Draw debug ring (visualize zones)
	UFUNCTION(BlueprintCallable)
	void DrawDebugRing();
};
