// Fill out your copyright notice in the Description page of Project Settings.


#include "Ninja/AI/AIPatrolManagerBase.h"

#include "Components/BillboardComponent.h"

// Sets default values
AAIPatrolManagerBase::AAIPatrolManagerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EditorBillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("EditBillboard"));
	EditorBillboardComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAIPatrolManagerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

TArray<AAIPatrolNodeBase*> AAIPatrolManagerBase::GetCurrentNodes() const
{
	//TODO: add Dynamic Ai Routes(https://trello.com/c/w5Xsy07O/7-dynamic-ai-routes)
	return Nodes;
}

// Called every frame
void AAIPatrolManagerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

