// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIPatrolNodeBase.generated.h"

/*
 * Base class for all partol nodes
 */
UCLASS()
class NINJA_API AAIPatrolNodeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIPatrolNodeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UBillboardComponent*EditorBillboardComponent;
	
	//How long will ai wait before moving to the next one
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Waiting)
	float WaitingTime = 1.f;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
