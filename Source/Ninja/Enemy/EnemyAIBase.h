// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Ninja/AI/AIInterface.h"
#include "Ninja/AI/AIPatrolManagerBase.h"
#include "Ninja/AI/AIState.h"



#include "EnemyAIBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetLostDelegate,FVector,LastKnownPosition);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetFoundDelegate,AActor*,Target);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFinishedSearchDelegate);

/**
 * 
 */
UCLASS()
class NINJA_API AEnemyAIBase : public AAIController,public IAIInterface
{
	GENERATED_BODY()
	protected:
	FVector LastTargetLocation;

	FTimerHandle NextPatrolPointTimerHandle;

	FTimerHandle SearchEndTimerHandle;
	public:

	UPROPERTY(BlueprintAssignable)
	FOnTargetLostDelegate OnTargetLost;


	UPROPERTY(BlueprintAssignable)
	FOnTargetFoundDelegate OnTargetFound;

	/*When reached last known location*/
	UPROPERTY(BlueprintAssignable)
	FFinishedSearchDelegate OnFinishedSearch;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=State)
	EAIState State = EAIState::EAS_Calm;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Search)
	float SearchTime = 10.f;

	/*If true - when search time is up it will go to Calm state
	 * If false - it will never be Calm after first sight
	 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Search)
	bool bEverEndsSearch = false;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Search)
	bool bIsCurrentlySearching = false;

	/*Used to avoid duplicate calls*/
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Patrolling)
	bool bIsWaitingOnPatrolPoint = false;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Patrolling)
	int32 CurrentPatrolPointId = -1;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Target)
	AActor*Target = nullptr;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Target)
	FName EnemyTag = TEXT("Player");

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Patrol)
	AAIPatrolManagerBase*CurrentPatrolManager = nullptr;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Blackboard)
	FName BlackboardTargetName = TEXT("Target");

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Blackboard)
	FName BlackboardPatrolNodeName = TEXT("CurrentPatrolNode");
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=Blackboard)
	FName BlackboardLastKnownLocationName = TEXT("LastKnownLocation");
	
	UFUNCTION(BlueprintCallable)
	void UpdateAI(TArray<AActor*>PerceivedActors);

	UFUNCTION(BlueprintCallable,Category = Search)
	void EndSearch();	

	UFUNCTION(BlueprintCallable)
	virtual void SelectNextPatrolPoint();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category=Target)
	void TargetLost();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category=Target)
    void TargetFound();

	virtual void OnReachedPatrolPoint_Implementation()override;

	virtual  void SelectNewPatrolPoint_Implementation()override;

	virtual void OnReachedLastKnownLocation_Implementation()override;

	virtual void ForceSetTarget_Implementation(AActor*newTarget)override;

	virtual void StartMeleeFight_Implementation(AActor*newTarget)override;

	virtual void UpdateAIState_Implementation(EAIState newState) override;

	virtual bool IsWaitingOnPatrolPoint_Implementation()override{return bIsWaitingOnPatrolPoint;}
};
