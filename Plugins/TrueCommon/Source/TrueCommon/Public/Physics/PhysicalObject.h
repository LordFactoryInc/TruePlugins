// (c) Lord Factory Inc.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "PhysicalObject.generated.h"

class UImpactAudioComponent;

/**
 * Physical Object actor: movable static mesh with enabled physics simulation and impact sound effects.
 */

UCLASS()
class TRUECOMMON_API APhysicalObject : public AStaticMeshActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, Category = "SFX")
	UImpactAudioComponent * ImpactAudioComponent;
	
public:

	APhysicalObject(const FObjectInitializer & ObjectInitializer);

public:

	virtual void NotifyHit(class UPrimitiveComponent * MyComp, AActor * Other, class UPrimitiveComponent * OtherComp, bool bSelfMoved, 
		FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit);
};
