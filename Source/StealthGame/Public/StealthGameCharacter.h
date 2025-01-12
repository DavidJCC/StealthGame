// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "StealthGameCharacter.generated.h"

class AGadgetBase;

UCLASS(Blueprintable)
class AStealthGameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	const float CamZoomValue = 50.f;
	const float CamMax = 2000.f;
	const float CamMin = 300.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CollisionComp, meta = (AllowPrivateAccess = "true"))
	USphereComponent* CollisionComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	float Health = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stealth|Sneak", meta = (AllowPrivateAccess = "true"))
	float StealthValue = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stealth|Sneak", meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* DefaultMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stealth|Sneak", meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* StealthMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gadget, meta = (AllowPrivateAccess = "true"))
	int32 NumTeleportGadgets = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gadget, meta = (AllowPrivateAccess = "true"))
	int32 NumDecoyGadgets = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gadget, meta = (AllowPrivateAccess = "true"))
	int32 NumDistractGadgets = 0;

	float StealthDecay = 0.3f;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<int32> NumGadgetsLeft;

	UPROPERTY(BlueprintReadOnly, Category = Stealth, meta = (AllowPrivateAccess = "true"))
	bool bIsInStealth = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stealth|Sneak", meta = (AllowPrivateAccess = "true"))
	USoundBase* DistractionNoise;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gadget, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AGadgetBase>> GadgetInventory;

	AGadgetBase* CurrentGadget;

	UPROPERTY(EditDefaultsOnly, Category = "Stealth|Sneak")
	bool bInfiniteStealth = false;

	UPROPERTY(EditDefaultsOnly, Category = Health)
	bool bInfiniteHealth = false;

	UPROPERTY(EditDefaultsOnly, Category = Gadget)
	bool bInfiniteGadgets = false;

	// If true then the player's rotation will match that of the cursor
	UPROPERTY(BlueprintReadOnly, Category = Gadget, meta = (AllowPrivateAccess = "true"))
	bool bThrowMode = false;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 InventoryIndex = 0;

	FName ThrowSocket = "ThrowSocket";

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsUsingGadget = false;

public:

	AStealthGameCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	virtual void Tick(float DeltaTime);

	virtual void BeginPlay();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UFUNCTION()
	void OnCollision(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ZoomCamIn();
	void ZoomCamOut();

	float GetHealth() const { return Health; }
	UFUNCTION(BlueprintCallable, Category = Health)
	void UpdateHealth(float pHealth);

	UFUNCTION(BlueprintCallable, Category = Stealth)
	float GetStealthValue();
	UFUNCTION(BlueprintCallable, Category = Stealth)
	void UpdateStealthValue(float pStealthValue, bool pUpdateCurrentValue = true /* If true the current stealth value will update*/);

	int32 GetNumSelectedGadget(int32 pArrayIndex);
	void UpdateNumSelectedGadget(int32 pArrayIndex, int32 pUpdateValue);

	UFUNCTION(BlueprintImplementableEvent)
	void DeathCheck();
	void StealthCheck();

	void ActivateStealth();
	void DeactivateStealth();
	bool IsInStealth() { return bIsInStealth; }

	// Stops the characters movement when space bar is pressed
	void StopMovement() { GetCharacterMovement()->StopMovementImmediately(); }

	void ThrowGadget();

	void ActivateThrowMode();
	void DeactivateThrowMode();
	void SetThrowMode(bool pThrowMode) { bThrowMode = pThrowMode; }

	void SelectTeleportGadget();
	void SelectDecoyGadget();
	void SelectDistractionGadget();

	bool CanSpawnGadget();

	// Called after a gadget is used to determine which gadget has been used so 
	// it can decrement the correct slot
	void DetermineNumGadgetAmount();

	UFUNCTION(BlueprintCallable, Category = Gadgets)
	void ClearInventory();

};

