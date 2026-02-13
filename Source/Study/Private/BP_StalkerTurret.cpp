#include "BP_StalkerTurret.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ABP_StalkerTurret::ABP_StalkerTurret()
{
    PrimaryActorTick.bCanEverTick = true;

    TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
    RootComponent = TurretMesh;

    DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
    DetectionSphere->SetupAttachment(RootComponent);
    DetectionSphere->SetSphereRadius(500.0f);
}

void ABP_StalkerTurret::BeginPlay()
{
    Super::BeginPlay();

    // 동적 바인딩: 이벤트와 함수를 연결함
    DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABP_StalkerTurret::OnOverlapBegin);
    DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &ABP_StalkerTurret::OnOverlapEnd);
}

void ABP_StalkerTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsDetected)
    {
        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        if (PlayerPawn)
        {
            // 터렛 위치에서 플레이어 위치를 바라보는 회전값 계산
            FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerPawn->GetActorLocation());
            
            // 터렛을 해당 방향으로 회전시킴
            SetActorRotation(LookAtRot);
        }
    }
}

void ABP_StalkerTurret::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this && OtherActor->IsA(APawn::StaticClass()))
    {
        bIsDetected = true;
        UE_LOG(LogTemp, Warning, TEXT("Player Detected!"));
    }
}

void ABP_StalkerTurret::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor != this && OtherActor->IsA(APawn::StaticClass()))
    {
        bIsDetected = false;
    }
}