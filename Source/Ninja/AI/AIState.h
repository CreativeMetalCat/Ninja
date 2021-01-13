// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "AIState.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EAIState:uint8
{
	EAS_Calm UMETA(DisplayName = "Calm"),
	EAS_Searching UMETA(DisplayName = "Searching"),
	EAS_Terrified UMETA(DisplayName = "Terrified"),
	EAS_InCombat UMETA(DisplayName = "InCombat"),
	/*When ai in this state perception checks don't happen to avoid loosing enemy because of sight
	 *Usage of this state implies having other means of checking if enemy is fighting
	 */
	EAS_InMeleeCombat UMETA(DisplayName = "InMeleeCombat")
};

