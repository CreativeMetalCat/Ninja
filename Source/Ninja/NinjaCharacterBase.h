// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Animation/OverlayType.h"
#include "GameFramework/Character.h"
#include "NinjaCharacterBase.generated.h"



class ANinjaCharacterBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathDelegate,ANinjaCharacterBase*,DeadPerson);

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
	UPROPERTY(BlueprintAssignable,Category=Death)
	FOnDeathDelegate OnDeath;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Animation|Turning")
	bool bIsTurningLeft = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Animation|Turning")
	bool bIsTurningRight = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Animation|Overlay")
	EOverlayType CurrentOverlay = EOverlayType::EOT_Default;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Life")
	bool bDead = false;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable)
    void SetIsTurning(float axisValue);

	//Declared in Base class to avoid casting
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category=Attack)
	bool CanBeStealthKilled();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category=Attack)
	void BeAttacked(ANinjaCharacterBase*Attacker,FName AttackName);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category=Attack)
	FTransform GetVictimTransform();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Attack|Animation")
	FName GetAttackAnimation();

	UFUNCTION(BlueprintCallable,Category=Attack)
	virtual bool CheckForAttack(TArray<AActor*>actors,ANinjaCharacterBase*&victim);
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category=Death)
	void Die();

};
