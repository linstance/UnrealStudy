// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "Camera/CameraComponent.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera -> SetupAttachment(RootComponent);
	Camera -> bUsePawnControlRotation = true;
	
	
	CylinderBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CylinderBody"));
    
	// 이것을 루트(캡슐)에 붙여서 같이 움직이게 합니다.
	CylinderBody->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using MyCharacter."));

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

	PlayerInputComponent->BindAxis("TurnCamera", this, &AMyCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::LookUp);
}


void AMyCharacter::MoveForward(float InputValue)
{
	FVector ForwardDirection = GetActorForwardVector();
	AddMovementInput(ForwardDirection, InputValue);
	
	if (InputValue != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), InputValue);
	}
}

void AMyCharacter::MoveRight(float InputValue)
{
	FVector RightDirection = GetActorRightVector();
	AddMovementInput(RightDirection, InputValue);
}

void AMyCharacter::Turn(float InputValue)
{
	AddControllerYawInput(InputValue);
}

void AMyCharacter::LookUp(float InputValue)
{
	AddControllerPitchInput(InputValue);
}

