// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ninja/NinjaCharacterBase.h"
#include "Ninja/AI/AIInterface.h"
#include "Ninja/AI/AIState.h"

#include "EnemyCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class NINJA_API AEnemyCharacterBase : public ANinjaCharacterBase,public IAIInterface
{
	GENERATED_BODY()
	public:
	/*Speed with which character will movebased on current state*/
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Movement)
	TMap<EAIState,float>MovementSpeed;

	virtual void UpdateAIState_Implementation(EAIState newState)override;
	
	virtual bool CanBeStealthKilled_Implementation()override;

	virtual void Die_Implementation()override;
};
