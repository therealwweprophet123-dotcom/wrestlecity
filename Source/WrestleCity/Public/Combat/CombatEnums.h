#pragma once

#include "CoreMinimal.h"

// Combat position in the ring - determines available moves
UENUM(BlueprintType)
enum class ECombatPosition : uint8
{
	Standing		UMETA(DisplayName = "Standing"),
	Rope			UMETA(DisplayName = "Rope"),
	Corner			UMETA(DisplayName = "Corner"),
	Running			UMETA(DisplayName = "Running"),
	Grounded		UMETA(DisplayName = "Grounded"),
	Apron			UMETA(DisplayName = "Apron"),
	Floor			UMETA(DisplayName = "Floor")
};

// Player input - maps to moves based on position and style
UENUM(BlueprintType)
enum class ECombatInput : uint8
{
	Strike			UMETA(DisplayName = "Strike"),
	Grapple			UMETA(DisplayName = "Grapple"),
	Whip			UMETA(DisplayName = "Whip"),
	Reverse			UMETA(DisplayName = "Reverse"),
	Interact		UMETA(DisplayName = "Interact"),
	None			UMETA(DisplayName = "None")
};

// Body part targeted - affects heat, blood, and recovery
UENUM(BlueprintType)
enum class EBodyPart : uint8
{
	Head			UMETA(DisplayName = "Head"),
	Body			UMETA(DisplayName = "Body"),
	Arm				UMETA(DisplayName = "Arm"),
	Leg				UMETA(DisplayName = "Leg"),
	None			UMETA(DisplayName = "None")
};

// Result of a move attempt - used for animation and reaction
UENUM(BlueprintType)
enum class EMoveResult : uint8
{
	Hit				UMETA(DisplayName = "Hit"),
	Reversed		UMETA(DisplayName = "Reversed"),
	Blocked			UMETA(DisplayName = "Blocked"),
	Countered		UMETA(DisplayName = "Countered"),
	Pinned			UMETA(DisplayName = "Pinned"),
	Miss			UMETA(DisplayName = "Miss")
};

// Wrestler alignment - affects crowd reaction and flag behavior
UENUM(BlueprintType)
enum class EAlignment : uint8
{
	Face			UMETA(DisplayName = "Face"),
	Heel			UMETA(DisplayName = "Heel"),
	Neutral			UMETA(DisplayName = "Neutral")
};

// Wrestling style - gates which moves are available
UENUM(BlueprintType)
enum class EWrestlingStyle : uint8
{
	Striker			UMETA(DisplayName = "Striker"),
	Technician		UMETA(DisplayName = "Technician"),
	Brawler			UMETA(DisplayName = "Brawler"),
	HighFlyer		UMETA(DisplayName = "High Flyer")
};

// Personality type - affects promo lines and behavioral flags
UENUM(BlueprintType)
enum class EPersonality : uint8
{
	Hothead			UMETA(DisplayName = "Hothead"),
	Loyal			UMETA(DisplayName = "Loyal"),
	Opportunist		UMETA(DisplayName = "Opportunist"),
	Veteran			UMETA(DisplayName = "Veteran"),
	Comedian		UMETA(DisplayName = "Comedian"),
	Arrogant		UMETA(DisplayName = "Arrogant")
};

// Flag types - track relationships, feuds, injuries, and story state
UENUM(BlueprintType)
enum class EFlagType : uint8
{
	Exposed			UMETA(DisplayName = "Exposed"),
	BloodFeud		UMETA(DisplayName = "Blood Feud"),
	TagSplit		UMETA(DisplayName = "Tag Split"),
	Scandal			UMETA(DisplayName = "Scandal"),
	WeaponWar		UMETA(DisplayName = "Weapon War"),
	RetirementTease	UMETA(DisplayName = "Retirement Tease"),
	Unreliable		UMETA(DisplayName = "Unreliable"),
	JumpShip		UMETA(DisplayName = "Jump Ship"),
	Invasion		UMETA(DisplayName = "Invasion"),
	HeadInjury		UMETA(DisplayName = "Head Injury")
};

// Ref strictness - affects ability to cheat and get away with it
UENUM(BlueprintType)
enum class ERefStrictness : uint8
{
	Lenient			UMETA(DisplayName = "Lenient"),
	Fair			UMETA(DisplayName = "Fair"),
	Strict			UMETA(DisplayName = "Strict")
};

// Match type - determines what rules apply and what counts
UENUM(BlueprintType)
enum class EMatchType : uint8
{
	Standard		UMETA(DisplayName = "Standard"),
	NoDQ			UMETA(DisplayName = "No Disqualification"),
	FallsCountAnywhere UMETA(DisplayName = "Falls Count Anywhere"),
	NoRopes			UMETA(DisplayName = "No Ropes"),
	Backyard		UMETA(DisplayName = "Backyard")
};

// Reversal type - used to track consecutive reversals for window shortening
UENUM(BlueprintType)
enum class EReversalType : uint8
{
	Strike			UMETA(DisplayName = "Strike Reversal"),
	Grapple			UMETA(DisplayName = "Grapple Reversal"),
	Finisher		UMETA(DisplayName = "Finisher Reversal")
};

// Pin attempt state - tracks pin situation and kickout chance
UENUM(BlueprintType)
enum class EPinState : uint8
{
	NotPinned		UMETA(DisplayName = "Not Pinned"),
	Pinned			UMETA(DisplayName = "Pinned"),
	KickedOut		UMETA(DisplayName = "Kicked Out"),
	Submitted		UMETA(DisplayName = "Submitted")
};
