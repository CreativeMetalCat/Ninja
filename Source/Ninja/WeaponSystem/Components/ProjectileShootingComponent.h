// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Ninja/WeaponSystem/BulletBase.h"
#include "Ninja/WeaponSystem/WeaponFireComponent.h"
#include "ProjectileShootingComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NINJA_API UProjectileShootingComponent : public UWeaponFireComponent
{
	GENERATED_BODY()
	public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TSubclassOf<ABulletBase>BulletClass;
	
	virtual void Fire_Implementation(FVector location,FRotator rotation)override;
};
