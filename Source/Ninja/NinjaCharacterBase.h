// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Animation/OverlayType.h"
#include "GameFramework/Character.h"
#include "NinjaCharacterBase.generated.h"

UCLASS()
class NINJA_API ANinjaCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANinjaCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Animation|Turning")
	bool bIsTurningLeft = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Animation|Turning")
	bool bIsTurningRight = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Animation|Overlay")
	EOverlayType CurrentOverlay = EOverlayType::EOT_Default;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable)
    void SetIsTurning(float axisValue);
};
