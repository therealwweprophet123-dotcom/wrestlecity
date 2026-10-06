#pragma once

#include "CoreMinimal.h"
#include "Combat/CombatEnums.h"
#include "MoveRow.generated.h"

USTRUCT(BlueprintType)
struct FMoveRow
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECombatPosition Position = ECombatPosition::Standing;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECombatInput Input = ECombatInput::Strike;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString MoveId = TEXT("jab_01");

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName AttackerAnim = TEXT("Strike_Jab");

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName DefenderAnim = TEXT("Stumble_Snap");

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HeatValue = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EBodyPart Limb = EBodyPart::Head;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ReverseWindow = 0.25f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StunDuration = 0.2f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bCanBeReversed = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsFinisher = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsStrongStrike = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsGrapple = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bAddsBlood = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TEnumAsByte<EWrestlingStyle>> AllowedStyles;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bForcesSetPosition = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ECombatPosition ForcedPosition = ECombatPosition::Standing;
};
