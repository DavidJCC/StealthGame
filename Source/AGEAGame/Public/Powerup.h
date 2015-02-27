// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Powerup.generated.h"

/**
 * 
 */
UCLASS()
class AGEAGAME_API APowerup : public AActor
{
	GENERATED_UCLASS_BODY()

	// True when the pickup is able to be picked up
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Up")
	bool bIsActive;

	// Collision sphere
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Power Up")
	USphereComponent* CollisionSphere;

	// Static mesh component
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Power Up")
	UStaticMeshComponent* PickupMesh;

	// The sound to play when the trigger is entered
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Up")
	USoundBase* PickupSound;

	// The rate in which the mesh will rotate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Up")
	float RotationRate;

	// Override the tick function
	virtual void Tick(float DeltaTime) override;
	
	virtual void OnCollision(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bHit, const FHitResult & hitresult);

};
