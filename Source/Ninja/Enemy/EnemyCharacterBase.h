// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ninja/NinjaCharacterBase.h"
#include "EnemyCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class NINJA_API AEnemyCharacterBase : public ANinjaCharacterBase
{
	GENERATED_BODY()
	public:
	
	virtual bool CanBeStealthKilled_Implementation()override;
};
