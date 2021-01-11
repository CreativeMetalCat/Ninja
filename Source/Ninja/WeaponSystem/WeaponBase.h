// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "WeaponInfo.h"
#include "GameFramework/Actor.h"
#include "Ninja/Weapon/WeaponAnimationType.h"
#include "WeaponBase.generated.h"

UCLASS()
class NINJA_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Components)
	UWeaponFireComponent*FireComponent;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category= Animation)
	EWeaponAnimationType AnimType = EWeaponAnimationType::EWAT_Rifle;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category= Ammo)
	int CurrentAmmo = 0;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category= Info)
	FWeaponInfo Info;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category= Info,meta = (ExposeOnSpawn = true))
	FDataTableRowHandle InfoRowHandle;

	UFUNCTION(BlueprintCallable)
	virtual bool LoadWeaponData();

	UFUNCTION(BlueprintCallable)
	virtual void Fire(FVector Location,FRotator Rotation);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
