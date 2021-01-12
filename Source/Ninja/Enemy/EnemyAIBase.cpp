// Fill out your copyright notice in the Description page of Project Settings.


#include "Ninja/Enemy/EnemyAIBase.h"

#include "BehaviorTree/BlackboardComponent.h"

void AEnemyAIBase::UpdateAI(TArray<AActor*> PerceivedActors)
{
	if(PerceivedActors.Num() > 0 && Blackboard)
	{
		if(PerceivedActors.Find(Target) != INDEX_NONE)
		{
			LastTargetLocation = Target->GetActorLocation();				
		}
		else
		{
			for (int i = 0; i < PerceivedActors.Num(); i++)
			{
				if(PerceivedActors[i]->Tags.Find(EnemyTag) != INDEX_NONE)
				{
					Target = PerceivedActors[i];
					TargetFound();
					return;
				}
			}
			
			TargetLost();

		}
	}
	else if(Blackboard)
	{
		TargetLost();
	}
}

void AEnemyAIBase::SelectNextPatrolPoint()
{
	if(CurrentPatrolManager && Blackboard)
	{
		CurrentPatrolPointId++;
		if(CurrentPatrolPointId > CurrentPatrolManager->GetCurrentNodes().Num() - 1)
		{
			CurrentPatrolPointId = 0;
		}
		Blackboard->SetValueAsObject(BlackboardPatrolNodeName,CurrentPatrolManager->GetCurrentNodes()[CurrentPatrolPointId]);
	}
	bIsWaitingOnPatrolPoint = false;
}

void AEnemyAIBase::OnReachedPatrolPoint_Implementation()
{
	if(!bIsWaitingOnPatrolPoint && CurrentPatrolManager)
	{
		bIsWaitingOnPatrolPoint = true;
		//we check if current node id is valid(in case the node was deleted)
		if(GetWorld() && CurrentPatrolManager->GetCurrentNodes().IsValidIndex(CurrentPatrolPointId))
		{
			if(CurrentPatrolManager->GetCurrentNodes()[CurrentPatrolPointId]->WaitingTime > 0)
			{
				//set timer for the next patrol point
				GetWorldTimerManager().SetTimer(NextPatrolPointTimerHandle, this, &AEnemyAIBase::SelectNextPatrolPoint,
                                                CurrentPatrolManager->GetCurrentNodes()[CurrentPatrolPointId]->WaitingTime, false);
				return;
			}
		}		
		//Node was deleted so we try to select new one
		SelectNextPatrolPoint();
	}
}

void AEnemyAIBase::SelectNewPatrolPoint_Implementation()
{
	SelectNextPatrolPoint();
}

void AEnemyAIBase::TargetFound_Implementation()
{
	if(Target)
	{
		Blackboard->SetValueAsObject(BlackboardTargetName,Target);
		
		OnTargetFound.Broadcast(Target);

		SetFocus(Target);
	}
}

void AEnemyAIBase::TargetLost_Implementation()
{
	if(Target)
	{
		Blackboard->ClearValue(BlackboardTargetName);

		OnTargetLost.Broadcast(LastTargetLocation);

		ClearFocus(EAIFocusPriority::Gameplay);

		Target = nullptr;
	}
}
