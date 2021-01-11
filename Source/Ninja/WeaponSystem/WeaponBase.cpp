// Fill out your copyright notice in the Description page of Project Settings.


#include "Ninja/WeaponSystem/WeaponBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	LoadWeaponData();
}

bool AWeaponBase::LoadWeaponData()
{
	if(!InfoRowHandle.IsNull())
	{
		if(FWeaponInfo* InfoPointer = InfoRowHandle.GetRow<FWeaponInfo>(""))
		{
			Info = *InfoPointer;
			if(!FireComponent || FireComponent->GetClass() != Info.WeaponFireComponent)
			{
				if(FireComponent){FireComponent->DestroyComponent();}
				FireComponent = NewObject<UWeaponFireComponent>(this,Info.WeaponFireComponent,TEXT("FireComponent"));
				FireComponent->RegisterComponent();			
			}
			
				
			
			return true;
		}
	}
	return false;
}

void AWeaponBase::Fire(FVector Location, FRotator Rotation)
{
	if(FireComponent)
	{
		FireComponent->Fire(Location,Rotation);
	}
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

