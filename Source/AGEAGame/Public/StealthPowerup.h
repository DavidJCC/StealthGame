// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Powerup.h"
#include "StealthPowerup.generated.h"

/**
 * 
 */
UCLASS()
class AGEAGAME_API AStealthPowerup : public APowerup
{
	GENERATED_BODY()
public:
	// The value to increase the player's stealth meter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stealth Power Up")
	float UpdateStealthValue = 10.0f;

	void OnPickedUp_Implementation() override;
	
	
};