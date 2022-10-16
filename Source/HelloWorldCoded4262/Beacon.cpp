// Fill out your copyright notice in the Description page of Project Settings.


#include "Beacon.h"

// Sets default values
ABeacon::ABeacon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Crea el colisionador
	collider = CreateDefaultSubobject<USphereComponent>("Collider");
	collider->SetSphereRadius(128, true);
	RootComponent = collider;

	//Crea la luz
	light = CreateDefaultSubobject<UPointLightComponent>("Light");
	light->AttachToComponent(collider, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

// Called when the game starts or when spawned
void ABeacon::BeginPlay()
{
	Super::BeginPlay();

	//Pone el color de la luz a verde
	SetLightColorGreen();
}

// Called every frame
void ABeacon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABeacon::SetTransitable()
{
	//Pone el color de la luz a verde
	SetLightColorGreen();

	//Si el array es mas que un coche elimina al primero que haya llegado tras darle permiso para pasar
	if (CarController.Num() > 0)
	{
		CarController[0]->bIsMoving = true;
		CarController.RemoveAt(0);

		//Pone el color de la luz a Rojo
		SetLightColorRed();
	}
}

void ABeacon::LetDisplacerGoThrough(ADisplacer* callingCar)
{
	//Comprueba que es un estado en el que se puede pasar (Verde)
	if (beaconColor == Green)
	{
		//Si es transitable le vuelve a dejar moverse y pone la luz a rojo
		callingCar->bIsMoving = true;
		SetLightColorRed();
	}

	//Si no se puede pasar (Rojo)
	else
	{
		//Se añade al array de coches
		CarController.Add(callingCar);
	}
}

void ABeacon::LeavingCar()
{
	//Inicia el timer y llama la función de Transitable
	GetWorld()->GetTimerManager().SetTimer(timerId, this, &ABeacon::SetTransitable, MoveTime, false);
}

void ABeacon::SetLightColorGreen()
{
	//Se cambia el color de la luz fisica
	light->SetLightColor(CGreen);

	//Se cambia el estado de color para la lógica de paso
	beaconColor = BeaconColor::Green;
}

void ABeacon::SetLightColorRed()
{
	//Se cambia el color de la luz fisica
	light->SetLightColor(CRed);

	//Se cambia el estado de color para la lógica de paso
	beaconColor = BeaconColor::Red;
}

