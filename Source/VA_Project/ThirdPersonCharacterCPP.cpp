// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonCharacterCPP.h"

// Sets default values
AThirdPersonCharacterCPP::AThirdPersonCharacterCPP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/**Устанавливается размер капсуль компоненты*/
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	/**Выключение зависимости камеры от поворота*/
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	/**Создание компоненты SpringArm*/
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 450.0f;
	CameraBoom->bUsePawnControlRotation = true;

	/**Создание компоненты камеры*/
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	/**Настройка MovementComponent*/
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 350.0f;
	GetCharacterMovement()->SetWalkableFloorAngle(60.0f);
}

// Called when the game starts or when spawned
void AThirdPersonCharacterCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThirdPersonCharacterCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AThirdPersonCharacterCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/** Привязка поворотов камеры */
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);

	/** Привязка прыжка и остановки */
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	/** Привязка движения по осям */
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AThirdPersonCharacterCPP::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AThirdPersonCharacterCPP::MoveRight);
}

void AThirdPersonCharacterCPP::MoveForward(float Axis)
{
	if ((Controller != NULL) && (Axis != 0.0f))
	{
		/**Получение угла направления камеры*/
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		/** Расчёт вектора движения */
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}

void AThirdPersonCharacterCPP::MoveRight(float Axis)
{
	if ((Controller != NULL) && (Axis != 0.0f))
	{
		/**Получение угла направления камеры*/
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		/** Расчёт вектора движения */
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}
