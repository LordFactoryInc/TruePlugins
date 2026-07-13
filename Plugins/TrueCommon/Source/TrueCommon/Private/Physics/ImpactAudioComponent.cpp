// (c) Lord Factory Inc.

#include "Physics/ImpactAudioComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

UImpactAudioComponent::UImpactAudioComponent()
	: ImpactEffectImpulseThreshold(1.0f)
	, ImpactEffectMaxImpulse(7.0f)
	, ImpactSound(nullptr)
{
	// Ticking is not needed by default
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;

	OnPropertiesChanged();
}

void UImpactAudioComponent::InitializeComponent()
{
	Super::InitializeComponent();

	AActor* owner = GetOwner();
	if (owner)
		owner->OnActorHit.AddDynamic(this, &UImpactAudioComponent::OnActorHit);
}

void UImpactAudioComponent::PostInitProperties()
{
	Super::PostInitProperties();

	OnPropertiesChanged();
}

void UImpactAudioComponent::PostLoad()
{
	Super::PostLoad();

	OnPropertiesChanged();
}

#if WITH_EDITOR
void UImpactAudioComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName& propertyName = PropertyChangedEvent.GetPropertyName();
	if (propertyName == GET_MEMBER_NAME_CHECKED(UImpactAudioComponent, ImpactEffectImpulseThreshold))
	{
		OnImpactEffectImpulseThresholdChanged();
	}
	else if (propertyName == GET_MEMBER_NAME_CHECKED(UImpactAudioComponent, ImpactEffectMaxImpulse))
	{
		OnImpactEffectMaxImpulseChanged();
	}
}
#endif

void UImpactAudioComponent::OnPropertiesChanged()
{
	OnImpactEffectImpulseThresholdChanged();
	OnImpactEffectMaxImpulseChanged();
}

void UImpactAudioComponent::SetImpactEffectImpulseThreshold(float InImpactEffectImpulseThreshold)
{
	ImpactEffectImpulseThreshold = InImpactEffectImpulseThreshold;
	OnImpactEffectImpulseThresholdChanged();
}

void UImpactAudioComponent::OnImpactEffectImpulseThresholdChanged()
{
	ImpactEffectImpulseThresholdSquared = FMath::Square(ImpactEffectImpulseThreshold);
}

void UImpactAudioComponent::SetImpactEffectMaxImpulse(float InImpactEffectMaxImpulse)
{
	ImpactEffectMaxImpulse = InImpactEffectMaxImpulse;
	OnImpactEffectMaxImpulseChanged();
}

void UImpactAudioComponent::OnImpactEffectMaxImpulseChanged()
{
	ImpactEffectMaxImpulseSquared = FMath::Square(ImpactEffectMaxImpulse);
}

void UImpactAudioComponent::OnActorHit(AActor* OwnerActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!ImpactSound)
		return;

	float sfxVolume = 0.0f;
	const float impulseSquared = NormalImpulse.SizeSquared();

	if (impulseSquared > ImpactEffectImpulseThresholdSquared)
	{
		// Play sound effect
		static const float ImpactEffectMinVolume = 0.01f;
		sfxVolume = FMath::Lerp(ImpactEffectMinVolume, 1.0f, FMath::Min(impulseSquared, ImpactEffectMaxImpulseSquared) / ImpactEffectMaxImpulseSquared);

		// Pass this as owning actor
		UGameplayStatics::PlaySoundAtLocation(OwnerActor, ImpactSound, Hit.ImpactPoint, FRotator::ZeroRotator, sfxVolume, 1.0f, 0.0f, nullptr, nullptr, OwnerActor);
	}

#if WITH_EDITOR
	if (EnableDebugLogs)
	{
		FString otherActorName = OtherActor ? OtherActor->GetName() : TEXT("NULL");
		FString otherClass = OtherActor ? OtherActor->GetClass()->GetName() : TEXT("");
		UPrimitiveComponent* otherComp = Hit.GetComponent();
		FString otherCompName = otherComp ? otherComp->GetName() : TEXT("NULL");
		bool otherSimulated = otherComp && otherComp->IsSimulatingPhysics();

		UE_LOG(LogTemp, Log, TEXT("ImpactAudio[%s]: hit by: %s[%s](comp: %s, sim: %d), blocking: %d, impulse: %.2f (squared: %.2f), sfx vol: %0.2f, loc: %.2f,%.2f,%.2f"), *OwnerActor->GetName(),
			*otherActorName, *otherClass, *otherCompName, otherSimulated, Hit.bBlockingHit, FMath::Sqrt(impulseSquared), impulseSquared, sfxVolume, Hit.Location.X, Hit.Location.Y, Hit.Location.Z);
	}
#endif
}
