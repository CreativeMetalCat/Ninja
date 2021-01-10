// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Ninja/NinjaCharacterBase.h"

#include "EnemyAIBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetLostDelegate,FVector,LastKnownPosition);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetFoundDelegate,AActor*,Target);
/**
 * 
 */
UCLASS()
class NINJA_API AEnemyAIBase : public AAIController
{
	GENERATED_BODY()
	protected:
	FVector LastTargetLocation;
	public:

	UPROPERTY(BlueprintAssignable)
	FOnTargetLostDelegate OnTargetLost;


	UPROPERTY(BlueprintAssignable)
	FOnTargetFoundDelegate OnTargetFound;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Target)
	AActor*Target = nullptr;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Target)
	FName EnemyTag = TEXT("Player");

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Blackboard)
	FName BlackboardTargetName = TEXT("Target");
	
	UFUNCTION(BlueprintCallable)
	void UpdateAI(TArray<AActor*>PercivedActors);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category=Target)
	void TargetLost();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category=Target)
    void TargetFound();
};
