#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_StalkerTurret.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class STUDY_API ABP_StalkerTurret : public AActor // STUDY_API로 수정됨
{
	GENERATED_BODY()

public:
	ABP_StalkerTurret();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* DetectionSphere;

	bool bIsDetected = false;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};