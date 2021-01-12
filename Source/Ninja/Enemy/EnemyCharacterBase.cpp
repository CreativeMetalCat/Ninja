// Fill out your copyright notice in the Description page of Project Settings.


#include "Ninja/Enemy/EnemyCharacterBase.h"

bool AEnemyCharacterBase::CanBeStealthKilled_Implementation()
{
	return !bDead;
}

void AEnemyCharacterBase::Die_Implementation()
{
	if(!bDead)
	{
		OnDeath.Broadcast(this);
		bDead = true;
	
		if(GetController())
		{
			auto Contr = GetController();
			GetController()->UnPossess();
			Contr->Destroy();
		}
	}
}
