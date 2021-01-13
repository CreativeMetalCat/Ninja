// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "OverlayType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EOverlayType : uint8
{
	EOT_Default UMETA(DisplayName = "Default"),
	EOT_Sword UMETA(DisplayName = "Sword"),
	EOT_Weapon UMETA(DisplayName = "Weapon"),
	EOT_HandCombat UMETA(DisplayName = "HandCombat")
};
