// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "Displacer.generated.h"

UCLASS()
class HELLOWORLDCODED4262_API ADisplacer : public AActor
{
	GENERATED_BODY()
	
public:	

	//Colisionador del objeto
	UPROPERTY(EditAnywhere, Category = "Collider")
		class UBoxComponent* boxCollider;

	//Malla del objeto
	UPROPERTY(EditAnywhere, Category = "Mesh")
		class UStaticMeshComponent* mesh;

	//Velocidad de desplazamiento del objeto
	UPROPERTY(EditAnywhere, Category = "Actor Data")
		float displacementSpeed = 10;

	//Velocidad de desplazamiento del objeto
	UPROPERTY(EditAnywhere, Category = "Actor Data")
		float lerpProgress = 0;

	//Indica el punto 1 del objeto (En el que comienza)
	UPROPERTY(EditAnywhere, Category = "Actor Data")
		class ATargetPoint *Start;

	//Indica el punto 2 del objeto (En el que acaba)
	UPROPERTY(EditAnywhere, Category = "Actor Data")
		class ATargetPoint *End;

	//Señala si esta volviendo o no
	UPROPERTY(EditAnywhere, Category = "Actor Data")
		bool bIsback = false;

	//Señala si se esta moviendo el objeto o no
	UPROPERTY(EditAnywhere, Category = "Actor Data")
		bool bIsMoving = true;

	//Constructor
	ADisplacer();

protected:

	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Configura a que dirección se mueve el Displacer
	void SetWay(bool isBack, float DeltaTime);

	UFUNCTION()
		void TriggerEnter(class UPrimitiveComponent* HitComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void TriggerExit(class UPrimitiveComponent* HitComp,
			class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);
};
