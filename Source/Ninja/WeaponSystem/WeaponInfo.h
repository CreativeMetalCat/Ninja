// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "WeaponFireComponent.h"
#include "Engine/DataTable.h"
#include "Ninja/Weapon/WeaponAnimationType.h"


#include "WeaponInfo.generated.h"

/**
 * Sturct that contains all of the info for the weapons
 */
USTRUCT(BlueprintType)
struct FWeaponInfo:public FTableRowBase
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Mesh)
	USkeletalMesh*WeaponMesh = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=CharacterAnimation)
	EWeaponAnimationType AnimType = EWeaponAnimationType::EWAT_Rifle;
	
	/*Whether does this weapon have skeletal animations with particles and sound built into it or not */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Animation)
	bool bHasAnimations = true;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Animation)
	UAnimMontage* ShootingMontage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Animation)
	UAnimMontage* ReloadingMontage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Shooting)
	float FireRate = 0.1f;

	/*How many bullets will be spawned for one ammo
	 *For example rifles - should have this at one and shotguns at more
	 * 
	 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Shooting)
	int BulletsPerShot = 1;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Shooting)
	TSubclassOf<UWeaponFireComponent>WeaponFireComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Spread)
	float Spread = 1.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Player)
	bool bAutoFire = false;
};