// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AIState.h"
#include "UObject/Interface.h"
#include "AIInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NINJA_API IAIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category=Patrolling)
	void OnReachedPatrolPoint();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category=Patrolling)
	void SelectNewPatrolPoint();

	/* Returns location for ai to look at when focused on this actor
	 * 
	 */
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category=Targeting)
	FVector GetMainTargetLocationOnBody();

	/*Use to quickly override current target*/
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category=Targeting)
	void ForceSetTarget(AActor*newTarget);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category=Targeting)
    void StartMeleeFight(AActor*newTarget);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category=Movement)
	void UpdateAIState(EAIState newState);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category=Search)
	void OnReachedLastKnownLocation();
};
