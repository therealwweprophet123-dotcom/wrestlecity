#pragma once

#include "CoreMinimal.h"
#include "Combat/CombatEnums.h"
#include "AnimationState.generated.h"

// ============================================================================
// 2D WRESTLING ANIMATION SYSTEM
// This explains how 2D sprite animations work for Fire Pro-style wrestling
// ============================================================================

// Animation state - what pose the wrestler is currently in
UENUM(BlueprintType)
enum class EAnimationState : uint8
{
	// Idle stance - standing and ready
	Idle,

	// Strike animation - throwing a punch or kick
	Strike,

	// Grapple animation - collar tie or clinch
	Grapple,

	// Stagger animation - being hit and stumbling back
	Stagger,

	// Grounded animation - knocked down on mat
	Grounded,

	// Rope press animation - pressed against ropes
	RopePress,

	// Corner trapped animation - stuck in corner
	CornerTrapped,

	// Pin animation - on back being pinned
	Pinned,

	// Running animation - dashing across ring with momentum
	Running,

	// Finisher animation - executing a big move
	Finisher,

	// Recovery animation - getting up from grounded
	Recovery
};

// Animation frame data - a single sprite frame
USTRUCT(BlueprintType)
struct FAnimationFrame
{
	GENERATED_BODY()

	// Index in the sprite sheet (0 = first frame, 1 = second frame, etc)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FrameIndex = 0;

	// How long this frame lasts (in seconds)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FrameDuration = 0.1f;

	// Offset for sprite pivot (visual position adjustment)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D SpriteOffset = FVector2D(0.0f, 0.0f);

	// Is this frame a "hit frame" (when damage applies)?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsHitFrame = false;

	// Sound effect to play at this frame
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SoundEffect = TEXT("");
};

// Animation clip - a sequence of frames
USTRUCT(BlueprintType)
struct FAnimationClip
{
	GENERATED_BODY()

	// Animation state this clip belongs to
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAnimationState AnimState = EAnimationState::Idle;

	// Which direction? (Right = 1, Left = -1)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FacingDirection = 1;

	// All frames in order
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FAnimationFrame> Frames;

	// Loop this animation?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bLoops = true;

	// Total duration of animation
	float GetTotalDuration() const
	{
		float Total = 0.0f;
		for (const FAnimationFrame& Frame : Frames)
		{
			Total += Frame.FrameDuration;
		}
		return Total;
	}
};

// Wrestler animation set - all animations for one wrestler
USTRUCT(BlueprintType)
struct FWrestlerAnimationSet
{
	GENERATED_BODY()

	// Wrestler name this belongs to
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WrestlerName = TEXT("Default");

	// Sprite sheet texture (contains all frames)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* SpriteSheet = nullptr;

	// Width of a single sprite frame in pixels
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FrameWidth = 128;

	// Height of a single sprite frame in pixels
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FrameHeight = 256;

	// All animation clips
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FAnimationClip> AnimationClips;

	// Get animation clip for a specific state
	FAnimationClip* GetAnimationClip(EAnimationState State);
};

// ============================================================================
// KEY CONCEPT: 2D SPRITE FRAME SYSTEM
// ============================================================================
/*
The 2D wrestling animation works like Fire Pro Wrestling:

Each wrestler has ONE big sprite sheet image with multiple frames arranged in order.
For example, a 2x4 grid of frames (8 total):

SPRITE SHEET (example):
┌───────────┬───────────┬───────────┬───────────┐
│ Idle      │ Punch 1   │ Punch 2   │ Punch 3   │  Row 1
├───────────┼───────────┼───────────┼───────────┤
│ Stagger 1 │ Stagger 2 │ Stumble 3 │ Recover   │  Row 2
└───────────┴───────────┴───────────┴───────────┘

Frame 0: Idle
Frame 1: Punch 1
Frame 2: Punch 2
Frame 3: Punch 3
Frame 4: Stagger 1
Frame 5: Stagger 2
Frame 6: Stumble 3
Frame 7: Recover

When a strike happens:
1. Wrestler plays "Punch" animation (frames 1, 2, 3)
2. Frame 2 is marked as "hit frame" - damage applies here
3. Opponent reacts with "Stagger" animation (frames 4, 5, 6)
4. After stagger ends, wrestler goes back to "Idle"

This is the ENTIRE animation system. No skeletal mesh deformation.
*/

// ============================================================================
// 2D SPRITE LAYOUT EXPLANATION
// ============================================================================
/*
Think of a wrestler sprite like this:

HEAD (expressive eyes, mouth)
╱╲ ╱╲ ← Two eyes, side-view profile
(__)(__) ← Eyes with pupils

TORSO (broad shoulders, visible muscles)
║ ║ ║ ║ ← Arms and body structure
╱ ╱╲╲╱ ← Legs in stance

Each animation frame shows a different pose of this silhouette.

IDLE: Standing neutral
┌─────────┐
│  ╱╲ ╱╲  │
│ (__)  │
│ ║ ║ ║ ║ │
│╱ ╱╲╲╱ ╲ │
└─────────┘

STRIKE (Punch): Arm extended
┌─────────┐
│  ╱╲  ║  │ ← Fist extended
│ (__)  │ ← Eyes focused
│ ║╱║ ║ ║ │ ← Body twisted
│╱ ╱╲╲╱ ╲ │
└─────────┘

STAGGER (Hit): Knocked back
┌─────────┐
│    ╱╲   │ ← Head back
│    ║ │ ← Eyes wide (surprised)
│  ║  ║ ║ │ ← Arms up in shock
│ ╱  ╱╲╲ │ ← Legs stumbling
└─────────┘

GROUNDED: On mat
┌─────────┐
│         │
│ ═════   │ ← Wrestler horizontal
│ ║ ║ ║ ║ │ ← Arms and legs visible
│         │
└─────────┘

ROPE PRESS: Against ropes
┌─────────┐
│  ╱╲ ║║║ │ ← Ropes on right
│ (__)║║║ │ ← Back against ropes
│ ║║║║║║ │ ← Arms around ropes
│╱╲╱╲║╲╱ │
└─────────┘
*/

// ============================================================================
// HIT FRAME TIMING CONCEPT
// ============================================================================
/*
A punch animation has 3 frames:

Frame 0: Punch setup (0.1 sec) - bIsHitFrame = false
Frame 1: Punch connection (0.1 sec) - bIsHitFrame = TRUE ← Damage applies HERE
Frame 2: Punch recovery (0.1 sec) - bIsHitFrame = false

When the animation plays:
- Frame 0: Play punch setup pose, no damage yet
- Frame 1: Play connection pose, APPLY DAMAGE NOW, play punch sound
- Frame 2: Play recovery pose, opponent starts stagger animation

This way, the animation is in sync with gameplay.
The "hit frame" is just a flag that says "when this frame is showing, 
the move has landed."
*/

// ============================================================================
// ANIMATION DIRECTION (LEFT vs RIGHT)
// ============================================================================
/*
In 2D fighting games, wrestlers face each other.
If Wrestler A is on the LEFT, they face RIGHT.
If Wrestler B is on the RIGHT, they face LEFT.

To handle this, either:

OPTION 1: Flip the sprite horizontally
- Store ONE sprite sheet facing right (the default)
- When wrestler faces left, flip the entire sprite

OPTION 2: Store both directions
- Sprite sheet has left-facing frames AND right-facing frames
- More art, but cleaner in code

For Fire Pro style, OPTION 1 is easier.
Just flip the sprite component's scale on the X axis.

Example:
- Wrestler A at position X = -1000: Scale.X = -1.0 (face right)
- Wrestler B at position X = +1000: Scale.X = +1.0 (face left)
*/

// ============================================================================
// RING ZONE ANIMATION MAPPING
// ============================================================================
/*
Different ring zones allow different animations:

STANDING ZONE:
- Idle, Strike, Grapple, Stagger, Recovery, Running
- Full move set available

ROPE ZONE:
- Idle, RopePress, Rebound, Stagger, Recovery
- Can't grapple (limited space)
- Rope press animation plays when hit

CORNER ZONE:
- Idle, CornerTrapped, Stagger, Recovery
- Trapped animation plays, very limited
- Can't escape easily

GROUNDED ZONE:
- Grounded, Recovery, Pinned
- Only ground attacks available
- Pin animation plays when pinning

This limits what animations can play based on position.
It's a simple way to enforce ring rules visually.
*/
