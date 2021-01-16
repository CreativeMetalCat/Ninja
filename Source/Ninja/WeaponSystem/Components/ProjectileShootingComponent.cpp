// Fill out your copyright notice in the Description page of Project Settings.


#include "Ninja/WeaponSystem/Components/ProjectileShootingComponent.h"
#include "DrawDebugHelpers.h"

#include "Kismet/KismetMathLibrary.h"
#include "Ninja/WeaponSystem/WeaponBase.h"

void UProjectileShootingComponent::Fire_Implementation(FVector location, FRotator rotation)
{
	if(GetOwner())
	{
		//TODO:Find a way to reduce casting
		if(AWeaponBase*OwningWeapon = Cast<AWeaponBase>(GetOwner()))
		{
			float Spread = OwningWeapon->Info.Spread;
			FVector Result;
			
			for (int i = 0; i < OwningWeapon->Info.BulletsPerShot; i++)
			{
				Result = FMath::VRandCone(UKismetMathLibrary::GetForwardVector(rotation),FMath::DegreesToRadians(Spread))*200.f;
				FActorSpawnParameters params;
				params.Owner = WeaponOwner;
				params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				if(ABulletBase * bullet  = GetWorld()->SpawnActor<ABulletBase>(BulletClass, location,rotation))
				{
					bullet->SphereCollisionComponent->IgnoreActorWhenMoving(WeaponOwner,true);		
				}
			}
		}
	}
}
