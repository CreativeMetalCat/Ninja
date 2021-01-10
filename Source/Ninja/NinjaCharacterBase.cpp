// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaCharacterBase.h"

// Sets default values
ANinjaCharacterBase::ANinjaCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANinjaCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANinjaCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANinjaCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANinjaCharacterBase::SetIsTurning(float axisValue)
{
	if(FMath::IsNearlyEqual(GetVelocity().Size(),0))
	{
		//check for turn right
		if(axisValue > 0.3f)
		{
			bIsTurningRight = true;
			bIsTurningLeft = false;
		}
		else
		{
			bIsTurningRight = false;
		}

		//check for turn left
		if(axisValue < -0.3f)
		{
			bIsTurningLeft = true;
		}
		else
		{
			bIsTurningLeft = false;
		}
	}
	else
	{
		//we are moving so not turing in place
		bIsTurningLeft = false;
		bIsTurningRight = false;
	}
}

FName ANinjaCharacterBase::GetAttackAnimation_Implementation()
{
	return TEXT("StabThrough");
}

bool ANinjaCharacterBase::CheckForAttack(TArray<AActor*> actors,ANinjaCharacterBase*&victim)
{
	victim = nullptr;
	if(actors.Num() > 0)
	{
		for (int i = 0; i < actors.Num(); i++)
		{
			if(ANinjaCharacterBase*character = Cast<ANinjaCharacterBase>(actors[i]))
			{
				if(character->CanBeStealthKilled())
				{
					victim = character;
					character->BeAttacked(this,GetAttackAnimation());
					return true;
				}
			}
		}
	}
	return false;
}

FTransform ANinjaCharacterBase::GetVictimTransform_Implementation()
{
	return FTransform();
}

void ANinjaCharacterBase::BeAttacked_Implementation(ANinjaCharacterBase*Attacker,FName AttackName)
{
	
}

bool ANinjaCharacterBase::CanBeStealthKilled_Implementation()
{
	return false;
}

void ANinjaCharacterBase::Die_Implementation()
{
	OnDeath.Broadcast(this);
}

