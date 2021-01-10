// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "WeaponAnimationType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EWeaponAnimationType:uint8
{
	EWAT_Rifle UMETA(DisplayName = "Rifle"),
	EWAT_Pistol UMETA(DisplayName = "Pistol"),
	EWAT_Shotgun UMETA(DisplayName = "Shotgun")
};
