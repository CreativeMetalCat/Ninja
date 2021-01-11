// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponFireComponent.generated.h"


UCLASS( Blueprintable,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NINJA_API UWeaponFireComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponFireComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta = (ExposeOnSpawn = true))
	AActor*WeaponOwner = nullptr;
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Fire(FVector location,FRotator rotation);
};
