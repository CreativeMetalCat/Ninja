// Fill out your copyright notice in the Description page of Project Settings.


#include "Ninja/Enemy/EnemyAIBase.h"

#include "BehaviorTree/BlackboardComponent.h"

void AEnemyAIBase::UpdateAI(TArray<AActor*> PercivedActors)
{
	if(PercivedActors.Num() > 0 && Blackboard)
	{
		if(PercivedActors.Find(Target) != INDEX_NONE)
		{
			LastTargetLocation = Target->GetActorLocation();				
		}
		else
		{
			TargetLost();

			for (int i = 0; i < PercivedActors.Num(); i++)
			{
				if(PercivedActors[i]->Tags.Find(EnemyTag) != INDEX_NONE)
				{
					Target = PercivedActors[i];
					TargetFound();
					break;
				}
			}
		}
	}
}

void AEnemyAIBase::TargetFound_Implementation()
{
	if(Target)
	{
		Blackboard->SetValueAsObject(BlackboardTargetName,Target);
		
		OnTargetFound.Broadcast(Target);
	}
}

void AEnemyAIBase::TargetLost_Implementation()
{
	if(Target)
	{
		Blackboard->SetValueAsObject(BlackboardTargetName,nullptr);

		OnTargetLost.Broadcast(LastTargetLocation);

		Target = nullptr;
	}
}
