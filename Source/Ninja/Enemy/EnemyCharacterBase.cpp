// Fill out your copyright notice in the Description page of Project Settings.


#include "Ninja/Enemy/EnemyCharacterBase.h"

#include "GameFramework/CharacterMovementComponent.h"

void AEnemyCharacterBase::UpdateAIState_Implementation(EAIState newState)
{
	TArray<EAIState>States;
	MovementSpeed.GetKeys(States);
	int id = States.Find(newState);
	if(id != INDEX_NONE)
	{
		if(UCharacterMovementComponent*comp = Cast<UCharacterMovementComponent>(GetMovementComponent()))
		{
			TArray<float>speeds;
			MovementSpeed.GenerateValueArray(speeds);
			comp->MaxWalkSpeed = speeds[id];
		}
	}
}

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
