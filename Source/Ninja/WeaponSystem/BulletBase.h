// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "BulletBase.generated.h"

UCLASS()
class NINJA_API ABulletBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	USphereComponent*SphereCollisionComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UProjectileMovementComponent*MovementComponent;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
