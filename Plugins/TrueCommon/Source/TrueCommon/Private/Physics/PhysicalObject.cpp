// (c) Lord Factory Inc.

#include "Physics/PhysicalObject.h"

#include "Physics/ImpactAudioComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"

APhysicalObject::APhysicalObject(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
	, ImpactAudioComponent(nullptr)
{
	// Create subobjects
	ImpactAudioComponent = CreateDefaultSubobject<UImpactAudioComponent>(TEXT("ImpactAudio"));
	ImpactAudioComponent->SetupAttachment(RootComponent);

	SetMobility(EComponentMobility::Movable);

	// Enable replication by default
	bStaticMeshReplicateMovement = true;

	UStaticMeshComponent * staticMeshComponent = GetStaticMeshComponent();
	
	staticMeshComponent->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
	// Ignore camera traces by default
	staticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	staticMeshComponent->SetSimulatePhysics(true);
	staticMeshComponent->SetNotifyRigidBodyCollision(true);

	staticMeshComponent->SetAngularDamping(0.01f);
}

void APhysicalObject::NotifyHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
}
