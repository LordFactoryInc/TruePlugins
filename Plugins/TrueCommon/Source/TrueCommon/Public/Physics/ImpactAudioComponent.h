// (c) Lord Factory Inc.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ImpactAudioComponent.generated.h"

class USoundBase;

/**
 * Impact Audio Component - plays a sound effect when physics simulated objects collide.
 */

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TRUECOMMON_API UImpactAudioComponent : public USceneComponent
{
	GENERATED_BODY()

public:

	UImpactAudioComponent();

	virtual void InitializeComponent() override;
	virtual void PostInitProperties() override;
	virtual void PostLoad() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:

	void OnImpactEffectImpulseThresholdChanged();
	void OnImpactEffectMaxImpulseChanged();
	void OnPropertiesChanged();

	UFUNCTION()
	void OnActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

public:

	float GetImpactEffectImpulseThreshold() const { return ImpactEffectImpulseThreshold; }

	UFUNCTION(BlueprintCallable)
	void SetImpactEffectImpulseThreshold(float InImpactEffectImpulseThreshold);

	float GetImpactEffectMaxImpulse() const { return ImpactEffectMaxImpulse; }

	UFUNCTION(BlueprintCallable)
	void SetImpactEffectMaxImpulse(float InImpactEffectMaxImpulse);

protected:

	UPROPERTY(EditAnywhere, BlueprintSetter = SetImpactEffectImpulseThreshold, Category = "Impact Audio")
	float ImpactEffectImpulseThreshold;

	UPROPERTY(EditAnywhere, BlueprintSetter = SetImpactEffectMaxImpulse, Category = "Impact Audio")
	float ImpactEffectMaxImpulse;

public:

	UPROPERTY(EditAnywhere, Category = "Impact Audio")
	USoundBase * ImpactSound;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "Impact Audio")
	bool EnableDebugLogs;
#endif

protected:

	float ImpactEffectImpulseThresholdSquared;
	float ImpactEffectMaxImpulseSquared;
};
