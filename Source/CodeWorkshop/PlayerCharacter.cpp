// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		Subsystem = ULocalPlayer::GetSubsystem
			<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(DefaultMapping, 0);
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent =
		CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,
			this, &APlayerCharacter::PlayerMove);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered,
			this, &APlayerCharacter::PlayerLook);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started,
			this, &ACharacter::Jump);
	}
}

void APlayerCharacter::PlayerMove(const FInputActionValue& Value)
{
	FVector2D MovementDirection = Value.Get<FVector2D>();
	if (PlayerController)
	{
		FVector ForwardVector =
			UKismetMathLibrary::GetForwardVector(CameraComponent->GetComponentRotation());
		FVector RightVector =
			UKismetMathLibrary::GetRightVector(CameraComponent->GetComponentRotation());
		AddMovementInput(ForwardVector, MovementDirection.Y);
		AddMovementInput(RightVector, MovementDirection.X);
	}
}

void APlayerCharacter::PlayerLook(const FInputActionValue& Value)
{
	FVector2D LookDirection = Value.Get<FVector2D>();
	if (PlayerController)
	{
		AddControllerYawInput(-LookDirection.X);
		AddControllerPitchInput(LookDirection.Y);
	}
}


