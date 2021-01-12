// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaCharacterBase.h"

// Sets default values
ANinjaCharacterBase::ANinjaCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMeshComponent->SetupAttachment(GetMesh(),"WeaponHolding");
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

bool ANinjaCharacterBase::CanShoot_Implementation()
{
	return bCanShoot && Weapon && !bDead;
}

void ANinjaCharacterBase::CreateWeapon_Implementation(FDataTableRowHandle WeaponInfo)
{
	if(!WeaponInfo.IsNull())
	{
		if(!Weapon)
		{
			Weapon = GetWorld()->SpawnActor<AWeaponBase>(AWeaponBase::StaticClass());
			Weapon->AttachToActor(this,FAttachmentTransformRules::SnapToTargetIncludingScale);
		}
		
		Weapon->InfoRowHandle = WeaponInfo;
		Weapon->CurrentAmmo = 0;
		if(Weapon->LoadWeaponData())
		{
			WeaponMeshComponent->SetSkeletalMesh(Weapon->Info.WeaponMesh);
			CurrentOverlay = EOverlayType::EOT_Weapon;
		}
	}
}

void ANinjaCharacterBase::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	if(GetMesh()->SkeletalMesh)
	{
		OutLocation = GetMesh()->GetSocketLocation(HeadSocketName);
		OutRotation = GetMesh()->GetSocketRotation(HeadSocketName);
	}
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

bool ANinjaCharacterBase::CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation, int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor) const
{
	static const FName NAME_AILineOfSight = FName(TEXT("TestPawnLineOfSight"));

	FHitResult HitResult;

	FCollisionQueryParams params = FCollisionQueryParams();
	params.AddIgnoredActor(IgnoreActor);

	if(SocketsToTestForVisibility.Num() > 0)
	{
		//check each socket for visibility
		for (int i = 0; i < SocketsToTestForVisibility.Num(); i++)
		{
			FVector socketLocation;
		
			if (GetMesh() != nullptr)
			{
				socketLocation = GetMesh()->GetSocketLocation(SocketsToTestForVisibility[i]);

				const bool bHitSocket = GetWorld()->LineTraceSingleByChannel(HitResult, ObserverLocation, socketLocation, ECollisionChannel::ECC_Visibility, params);

				NumberOfLoSChecksPerformed++;
				
				if (bHitSocket == false || (HitResult.Actor.IsValid() && HitResult.Actor->IsOwnedBy(this))) {
					OutSeenLocation = socketLocation;
					OutSightStrength = 1;

					return true;
				}
			}
		}

	}
	
	//do default check to avoid invisible pawns
	const bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, ObserverLocation, GetActorLocation(), ECollisionChannel::ECC_Visibility, params);
			
	if (bHit == false || (HitResult.Actor.IsValid() && HitResult.Actor->IsOwnedBy(this)))
	{
		OutSeenLocation = GetActorLocation();
		OutSightStrength = 1;

		return true;
	}

	OutSightStrength = 0;
	
	return false;
}

