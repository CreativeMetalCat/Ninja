// Fill out your copyright notice in the Description page of Project Settings.


#include "Ninja/Enemy/EnemyAIBase.h"

#include "BehaviorTree/BlackboardComponent.h"

void AEnemyAIBase::UpdateAI(TArray<AActor*> PerceivedActors)
{
	//we don't want to accidentally loose sight of target because of ai spinning too fast
	if(State != EAIState::EAS_InMeleeCombat)
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
}

void AEnemyAIBase::EndSeach()
{
	if(Cast<IAIInterface>(GetPawn()) || GetPawn()->Implements<UAIInterface>())
	{
		IAIInterface::Execute_UpdateAIState(GetPawn(),EAIState::EAS_Searching);
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

void AEnemyAIBase::OnReachedLastKnownLocation_Implementation()
{
	OnFinishedSearch.Broadcast();

	Blackboard->ClearValue(BlackboardLastKnownLocationName);
}

void AEnemyAIBase::ForceSetTarget_Implementation(AActor* newTarget)
{
	if(newTarget && newTarget != Target)
	{
		Target = newTarget;
		
		if(SearchEndTimerHandle.IsValid()){SearchEndTimerHandle.Invalidate();}
		
		Blackboard->SetValueAsObject(BlackboardTargetName,Target);
		
		OnTargetFound.Broadcast(Target);

		SetFocus(Target);

		if(Cast<IAIInterface>(GetPawn()) || GetPawn()->Implements<UAIInterface>())
		{
			IAIInterface::Execute_UpdateAIState(GetPawn(),EAIState::EAS_InCombat);
		}
		
		State = EAIState::EAS_InCombat;
	}
}

void AEnemyAIBase::StartMeleeFight_Implementation(AActor* newTarget)
{
	if(newTarget && newTarget != Target)
	{
		Target = newTarget;
		
		if(SearchEndTimerHandle.IsValid()){SearchEndTimerHandle.Invalidate();}
		
		Blackboard->SetValueAsObject(BlackboardTargetName,Target);
		
		OnTargetFound.Broadcast(Target);

		SetFocus(Target);

		if(Cast<IAIInterface>(GetPawn()) || GetPawn()->Implements<UAIInterface>())
		{
			IAIInterface::Execute_UpdateAIState(GetPawn(),EAIState::EAS_InMeleeCombat);
		}
		
		State = EAIState::EAS_InMeleeCombat;
	}
}

void AEnemyAIBase::TargetFound_Implementation()
{
	if(Target)
	{
		if(SearchEndTimerHandle.IsValid()){SearchEndTimerHandle.Invalidate();}
		
		Blackboard->SetValueAsObject(BlackboardTargetName,Target);
		
		OnTargetFound.Broadcast(Target);

		SetFocus(Target);

		if(Cast<IAIInterface>(GetPawn()) || GetPawn()->Implements<UAIInterface>())
		{
			IAIInterface::Execute_UpdateAIState(GetPawn(),EAIState::EAS_InCombat);
		}
		
		State = EAIState::EAS_InCombat;
	}
}

void AEnemyAIBase::TargetLost_Implementation()
{
	if(Target)
	{
		Blackboard->ClearValue(BlackboardTargetName);

		OnTargetLost.Broadcast(LastTargetLocation);

		Blackboard->SetValueAsVector(BlackboardLastKnownLocationName,LastTargetLocation);

		ClearFocus(EAIFocusPriority::Gameplay);

		Target = nullptr;
	

		if(Cast<IAIInterface>(GetPawn()) || GetPawn()->Implements<UAIInterface>())
		{
			IAIInterface::Execute_UpdateAIState(GetPawn(),EAIState::EAS_Searching);
		}

		State = EAIState::EAS_Searching;
		
		if(bEverEndsSearch)
		{
			GetWorldTimerManager().SetTimer(SearchEndTimerHandle,this,&AEnemyAIBase::EndSeach,SearchTime);
		}
	}
}
