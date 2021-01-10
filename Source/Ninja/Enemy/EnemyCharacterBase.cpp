// Fill out your copyright notice in the Description page of Project Settings.


#include "Ninja/Enemy/EnemyCharacterBase.h"

bool AEnemyCharacterBase::CanBeStealthKilled_Implementation()
{
	return !bDead;
}
