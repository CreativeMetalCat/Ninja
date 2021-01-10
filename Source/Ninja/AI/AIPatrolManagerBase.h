// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AIPatrolNodeBase.h"
#include "GameFramework/Actor.h"
#include "AIPatrolManagerBase.generated.h"

/*This class Manages ai's patrol route.
 * It is preferable to have one manager for each ai to avoid path issues
 * 
 */
UCLASS()
class NINJA_API AAIPatrolManagerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIPatrolManagerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UBillboardComponent*EditorBillboardComponent;

	/*All nodes the ai should go through*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Nodes,meta=(ExposeOnSpawn = true))
	TArray<AAIPatrolNodeBase*> Nodes;

	UFUNCTION(BlueprintPure,Category=Nodes)
	virtual TArray<AAIPatrolNodeBase*> GetCurrentNodes()const;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
