#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Components/PointLightComponent.h"
#include "Displacer.h"
#include "GameFramework/Actor.h"
#include "Beacon.generated.h"

UCLASS()
class HELLOWORLDCODED4262_API ABeacon : public AActor
{
	GENERATED_BODY()
	
public:	

	//Colisionador del objeto
	UPROPERTY(EditAnywhere, Category = "Collider")
		class USphereComponent* collider;

	//Colisionador del objeto
	UPROPERTY(VisibleAnywhere, Category = "Collider")
		TArray<ADisplacer*> CarController;

	//Colisionador del objeto
	UPROPERTY(VisibleAnywhere, Category = "Collider")
		float MoveTime = 0.5f;

	//Estado de la baliza
	enum BeaconColor { Red, Green };
	BeaconColor beaconColor;

	//https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/Engine/FTimerHandle/
	//Manejador que identifica a un timer de manera única
	FTimerHandle timerId;

	//Punto de Luz
	UPointLightComponent* light;

	//Constructor
	ABeacon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Colores de la Luz
	FLinearColor CRed = FLinearColor(255, 0, 0);
	FLinearColor CGreen = FLinearColor(0, 255, 0);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Pone el color de la PointLight a Rojo
	UFUNCTION()
		void SetLightColorRed();

	//Pone el color de PointLight a Verde
	UFUNCTION()
		void SetLightColorGreen();

	//Comprueba si hay mas coches que necesiten pasar
	UFUNCTION()
		void SetTransitable();

	//Deja pasar al displacer
	UFUNCTION()
		void LetDisplacerGoThrough(ADisplacer* callingCar);

	//Displacer abandona el semaforo
	UFUNCTION()
		void LeavingCar();

};
