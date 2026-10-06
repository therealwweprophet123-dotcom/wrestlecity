#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Combat/CombatEnums.h"
#include "Interaction2D.generated.h"

// ============================================================================
// 2D ARCADE WRESTLING FIGHT INTERACTION SYSTEM
// Side-View, Chunky Sprites, Button Mashing with Timing Windows
// Like: Fire Pro Wrestling, WWE All Stars (2D mode), Wrestlemania Arcade
// ============================================================================

/*
THIS IS HOW 2D ARCADE WRESTLING WORKS:

THE SCREEN VIEW:
┌─────────────────────────────────────────────────────────────────┐
│ CROWD (background blur, cheering)                              │
├─────────────────────────────────────────────────────────────────┤
│                                                                  │
│  [WRESTLER 1]                    RING                [WRESTLER 2]│
│   64x128 sprite                (ropes visible)       64x128 sprite
│   facing RIGHT                                       facing LEFT
│
│  Health: ████████░░ 80%       Crowd Heat: ████░░░░░░ 45%
│  Spirit: ████░░░░░░ 50%       Finisher:   ██░░░░░░░░ 20%
│
│                           [TIMING WINDOW]
│                    Press X NOW for PERFECT!
│                        ▮▮▮▮▮▮▯▯▯
│                        0.1s / 0.5s
│
└─────────────────────────────────────────────────────────────────┘

THE GAMEPLAY:

Player sees opponent preparing attack animation.
Screen shows: "PRESS X!" or flashes red.
Player must press X within the narrow perfect window (0.1s).
If pressed at right time: Green "PERFECT!" appears, big damage, crowd cheers.
If pressed late: Yellow "GOOD" appears, normal damage.
If missed: Red "MISS" appears, no damage, crowd boos.
After hit, defender stumbles back in stagger animation.
After stagger, opponent can press reverse button to counter (very tight window).

This repeats until someone's health = 0.
*/

// ============================================================================
// 2D ARCADE INTERACTION PROMPT - Visual cue on screen
// ============================================================================

UENUM(BlueprintType)
enum class E2DPromptType : uint8
{
	// "PRESS X!" - Basic attack button prompt
	PressButton,

	// "MASH X!" - Repeated button presses for power
	MashButton,

	// "COUNTER!" - Time your reverse perfectly
	ReverseNow,

	// "FINISHER!" - Special button combo ready
	FinisherReady,

	// Silent - No prompt (enemy attacking)
	Silent
};

// ============================================================================
// 2D TIMING VISUAL - What appears on screen
// ============================================================================

UENUM(BlueprintType)
enum class E2DTimingVisual : uint8
{
	// Green text, gold screen flash, crowd cheer
	Perfect,

	// Blue text, white pulse, crowd ok
	Good,

	// Yellow text, orange pulse, crowd uncertain
	Late,

	// Red text, red flash, crowd boos
	Missed,

	// Gray text, no effect, crowd silent
	Failed
};

// ============================================================================
// 2D INTERACTION STATE - What's happening on screen right now
// ============================================================================

USTRUCT(BlueprintType)
struct F2DInteractionState
{
	GENERATED_BODY()

	// Current visual prompt type
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E2DPromptType CurrentPrompt = E2DPromptType::Silent;

	// Timing window progress (0.0 to 1.0)
	// 0.0 = window just opened
	// 0.5 = halfway through
	// 1.0 = window closed
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WindowProgress = 0.0f;

	// Perfect timing zone (as % of window)
	// 0.0 to 0.2 = perfect zone (first 20% of window)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PerfectZoneEnd = 0.2f;

	// Display health bar visual
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthBarPercent = 1.0f;

	// Display spirit bar visual
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpiritBarPercent = 0.5f;

	// Display crowd heat bar visual
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CrowdHeatBarPercent = 0.5f;

	// Display finisher meter visual
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FinisherMeterPercent = 0.0f;

	// Current animation frame index
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentFrameIndex = 0;

	// Total frames in current animation
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TotalAnimationFrames = 1;

	// Wrestler 1 position on screen
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Wrestler1ScreenPos = FVector2D(200.0f, 400.0f);

	// Wrestler 2 position on screen
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Wrestler2ScreenPos = FVector2D(1720.0f, 400.0f);

	// Is wrestler 1 facing right (true) or left (false)?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bWrestler1FacingRight = true;

	// Is wrestler 2 facing right (true) or left (false)?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bWrestler2FacingRight = false;

	// Currently attacking wrestler (0 or 1)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackingWrestlerIndex = 0;

	// Current timing visual feedback
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E2DTimingVisual CurrentTimingVisual = E2DTimingVisual::Good;

	// Damage pop-up text (floating number like "+25")
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DamagePopupText = TEXT("");

	// Show damage popup?
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShowDamagePopup = false;

	// Damage popup position
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D DamagePopupPos = FVector2D(0.0f, 0.0f);
};

// ============================================================================
// 2D ARCADE INTERACTION SYSTEM
// ============================================================================

UCLASS()
class WRESTLECITY_API U2DArcadeInteractionSystem : public UObject
{
	GENERATED_BODY()

public:
	U2DArcadeInteractionSystem();

	// ========== TIMING WINDOW ==========

	// Open a timing window (0.5 seconds for attack, 0.25 for reverse)
	UFUNCTION(BlueprintCallable)
	void OpenTimingWindow(float WindowDuration, float PerfectZoneDuration);

	// Close the current window
	UFUNCTION(BlueprintCallable)
	void CloseTimingWindow();

	// Tick the timing window (call every frame)
	UFUNCTION(BlueprintCallable)
	void TickTimingWindow(float DeltaTime);

	// Check if player pressed button in time
	UFUNCTION(BlueprintCallable)
	E2DTimingVisual CheckButtonPress();

	// ========== SCREEN PROMPTS & VISUALS ==========

	// Show "PRESS X!" prompt on screen
	UFUNCTION(BlueprintCallable)
	void ShowPrompt(E2DPromptType PromptType, float Duration);

	// Show floating damage number like "+25"
	UFUNCTION(BlueprintCallable)
	void ShowDamagePopup(float Damage, FVector2D ScreenPosition);

	// Show hit effect (flash, shake)
	UFUNCTION(BlueprintCallable)
	void ShowHitEffect(E2DTimingVisual TimingQuality);

	// Show crowd reaction (cheer or boo)
	UFUNCTION(BlueprintCallable)
	void PlayCrowdReaction(E2DTimingVisual TimingQuality);

	// Play sound effect for hit
	UFUNCTION(BlueprintCallable)
	void PlayHitSound(E2DTimingVisual TimingQuality);

	// ========== BAR DISPLAYS ==========

	// Update health bar display
	UFUNCTION(BlueprintCallable)
	void UpdateHealthBar(int32 WrestlerIndex, float HealthPercent);

	// Update spirit bar display
	UFUNCTION(BlueprintCallable)
	void UpdateSpiritBar(int32 WrestlerIndex, float SpiritPercent);

	// Update crowd heat bar display
	UFUNCTION(BlueprintCallable)
	void UpdateCrowdHeatBar(float HeatPercent);

	// Update finisher meter display
	UFUNCTION(BlueprintCallable)
	void UpdateFinisherMeter(int32 WrestlerIndex, float MeterPercent);

	// ========== ANIMATION SYNC ==========

	// Get current animation frame index
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentFrameIndex() const;

	// Set total frames for current animation
	UFUNCTION(BlueprintCallable)
	void SetAnimationFrameCount(int32 FrameCount);

	// Is current frame a "hit frame" (when damage applies)?
	UFUNCTION(BlueprintCallable)
	bool IsCurrentFrameHitFrame() const;

	// ========== STATE ==========

	UPROPERTY()
	F2DInteractionState InteractionState;

	UPROPERTY()
	float TimingWindowTimer = 0.0f;

	UPROPERTY()
	float TimingWindowDuration = 0.5f;

	UPROPERTY()
	float PerfectZoneDuration = 0.1f;

	UPROPERTY()
	bool bWindowIsOpen = false;
};

// ============================================================================
// 2D ARCADE COMBAT EXAMPLE
// ============================================================================

/*
EXAMPLE FIGHT SEQUENCE IN 2D ARCADE STYLE:

SETUP:
┌────────────────────────────────────────────────┐
│ WRESTLER 1 (Red)      vs      WRESTLER 2 (Blue)│
│   Health: ████████░░ 80%        ██████████ 100%│
│   Spirit: ████░░░░░░ 50%        ████░░░░░░ 40% │
│ Crowd: ████░░░░░░░░ 40% (bored)                │
└────────────────────────────────────────────────┘

STEP 1: WRESTLER 1 ATTACKS
───────────────────────────
Screen shows: Red sprite winds up for punch
Animation plays: 3 frames
  Frame 0 (0.0-0.07s): "PRESS X!" prompt appears + timer bar
  Frame 1 (0.07-0.13s): ▮▮▮▮▮▯▯▯ (0.1s / 0.5s)
  Frame 2 (0.13-0.2s):  ▮▮▮▮▮▮▯▯ Perfect zone ENDING

Player must press X within this time.

PERFECT TIMING (Player presses at 0.08s):
  ✓ Green "PERFECT!" text appears on screen
  ✓ Screen flashes gold/yellow
  ✓ Damage = 5.0 × 1.25 (perfect multiplier) = 6.25
  ✓ Crowd Heat: +10 (crowd cheers)
  ✓ Finisher Meter: +3 (bonus for perfect)
  
Animation frame 1 is the "hit frame" → damage applies right now
Blue wrestler gets knocked back

GOOD TIMING (Player presses at 0.2s):
  ◐ Blue "GOOD" text appears
  ◐ Screen pulses slightly
  ◐ Damage = 5.0 × 1.0 (normal) = 5.0
  ◐ Crowd Heat: +5 (crowd ok)
  ◐ Finisher Meter: +1 (normal)
  
Red wrestler pushes through, blue wrestler staggers

MISSED TIMING (Player presses at 0.6s):
  ✗ Red "MISSED!" text appears
  ✗ Screen does nothing
  ✗ Damage = 0.0 (NO HIT)
  ✗ Crowd Heat: -5 (crowd boos)
  ✗ Finisher Meter: +0
  
Red wrestler's punch doesn't connect, blue wrestler laughs

STEP 2: DEFENDER REACTS
───────────────────────
Blue sprite plays stagger animation:
  Frame 0: Back leg plants
  Frame 1: Arms flail up
  Frame 2: Torso tilts back
  Frame 3-4: Recover stance

During stagger, Blue wrestler's health bar drops:
  Before: ██████████ 100%
  After:  ██████░░░░ 60% (-40 damage)
  
Sprite moves slightly back on screen

STEP 3: REVERSAL WINDOW OPENS
──────────────────────────────
After Blue recovers, screen shows:
  "COUNTER!" prompt (0.25 second window)
  ▮▯▯ (0.05s / 0.25s perfect zone)

If Blue presses REVERSE within 0.05s:
  ✓ "COUNTER!" text in yellow
  ✓ Roles SWAP: Blue now attacking, Red defending
  ✓ Crowd heat: +8 (crowd loves reversal)

If Blue misses window:
  ✗ Nothing happens, it's Red's turn again

STEP 4: RED ATTACKS AGAIN
──────────────────────────
Red opens another timing window
Player sees "PRESS X!" + timer bar ▮▮▯▯▯

But this time, Red has been building crowd heat:
  Crowd Heat: 45% → Damage multiplier = 1.1x
  
Red's strike does:
  5.0 × 1.25 (perfect) × 1.1 (crowd) = 6.875 damage
  
Blue is knocked down (health < 30%)

STEP 5: BLUE IS GROUNDED
────────────────────────
Blue sprite shows knocked down animation:
  Horizontal sprite on mat
  
Blue has limited options:
  - Recovery animation (press X to get up faster)
  - Kickout attempt (press X to avoid pin)
  - Stay down (lose by count-out in 10 seconds)

Screen shows:
  Count: 1, 2, 3... (ref counting)
  Recovery Timer: ████░░░░░░ 5 seconds

Blue player presses X to get up.
Blue plays recovery animation.
Blue stands back up, health at 15% (low health)

STEP 6: FINISHER AVAILABLE
───────────────────────────
Red's finisher meter is full:
  Finisher: ██████████ 100% READY!
  
Screen shows: "FINISHER READY! Press LB+RB!"
  Or "FINISHER READY! Press L+R!"

Red player presses special buttons.
1.0 second timing window opens (VERY tight)
  ▮▯ (0.1s / 1.0s perfect zone)

Red's sprite plays HUGE finisher animation:
  Large, exaggerated moves
  2+ seconds long animation
  Screen shakes
  Crowd goes ABSOLUTELY WILD

If perfect timing:
  ✓ "FINISHER!" (gold screen flash)
  ✓ Blue takes 15.0 damage (3x multiplier!)
  ✓ Blue's health = 0%
  ✗ MATCH OVER - Red wins!
  ✓ Victory animation plays
  ✓ Crowd chants Red's name
  ✓ Final screen: VICTORY! CROWD: 100%

---

VISUAL DISPLAY THROUGHOUT:

Top Bar (Status):
┌─────────────────────────────────────────────────────┐
│ RED: ████████░░ 80%    Blue: ██████░░░░ 60%        │
│      Spirit ████░░░░   Spirit ███░░░░░░░           │
└─────────────────────────────────────────────────────┘

Middle (Fighters & Crowd):
┌─────────────────────────────────────────────────────┐
│         CROWD (animated, cheering)                  │
│                                                     │
│ [RED SPRITE] ←────RING────→ [BLUE SPRITE]         │
│                                                     │
│ Crowd Heat: ████░░░░░░░░ 40% (bored)              │
└─────────────────────────────────────────────────────┘

Bottom (Prompts & Meters):
┌─────────────────────────────────────────────────────┐
│ "PRESS X FOR STRIKE!"                              │
│ Timing: ▮▮▮▯▯▯  [0.1s / 0.5s]                    │
│                                                     │
│ RED Finisher: ██░░░░░░░░ 20%                      │
│ BLUE Finisher: ████░░░░░░ 40%                     │
│                                                     │
│ "COUNTER!" ▮▯▯▯  [REVERSAL WINDOW]               │
└─────────────────────────────────────────────────────┘

---

KEY 2D ARCADE MECHANICS:

1. TIMING BARS (visual progress)
   ▮▮▯▯▯ ← Shows progress through timing window
   Perfect zone = first 20% (▮▮)
   Normal zone = next 60% (▮▮▮▯)
   Late zone = last 20% (▮▯)

2. FLOATING TEXT
   Green "PERFECT!" - appears at hit location, bounces up, fades
   Yellow "GOOD" - smaller, white pulse
   Red "MISSED!" - bold, screen shakes

3. FLOATING NUMBERS
   +25 ← Damage dealt (orange text, floats up)
   -10 ← Damage taken (red text, floats down)

4. SCREEN EFFECTS
   Perfect: Full screen flash (gold), screen shake (large)
   Good: Small pulse, no shake
   Missed: Red tint flash, buzzer sound

5. ANIMATION SYNCHRONIZATION
   Punch animation 0.2s total
   Hit frame at 0.1s (halfway)
   If player presses at hit frame = PERFECT connection
   Stagger animation plays immediately after hit frame

6. CROWD ENERGY (visual bar)
   0-25%: Gray bar, boos (sad crowd faces)
   25-50%: Yellow bar, murmurs (neutral crowd)
   50-75%: Orange bar, cheers (happy crowd)
   75-100%: Red bar, wild (crazy crowd, confetti)
   
   Crowd affects:
   - Damage output (0.75x to 1.25x)
   - Recovery speed (faster when crowd is hot)
   - Visual effects (more screen shakes when hot)
   - Audio (louder cheers when hot)

7. BAR DISPLAYS
   Health: Left side of each wrestler, decreases from right to left
   Spirit: Below health, thin bar, can increase (kickout)
   Crowd: Bottom center, wide bar showing global heat
   Finisher: Right side of each wrestler, pips or segments filling

8. RING ZONE VISUAL INDICATORS
   Standing: Both wrestlers centered on screen
   Rope: Wrestler gets pushed to edge of screen, ropes visible
   Corner: Wrestler forced into corner, turnbuckle visual
   Grounded: Wrestler sprite rotates horizontal
   Running: Wrestler sprite zoomed out, movement blur effect
   Apron: Wrestler outside ring ring boundary
   Floor: Wrestler furthest from ring, count timer visible
*/
