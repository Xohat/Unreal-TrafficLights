#include "Displacer.h"
#include "Beacon.h"

// Sets default values
ADisplacer::ADisplacer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Crea el componente Collider
	boxCollider = CreateDefaultSubobject<UBoxComponent>("Collider");

	//Establece la medida del collider
	boxCollider->SetBoxExtent(FVector(50, 50, 50));

	//Establece la raíz en la jerarquía de componentes
	SetRootComponent(boxCollider);

	//Crea el componente Malla
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	//Modifica la jerarquía de componentes
	mesh->AttachToComponent(boxCollider, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

// Called when the game starts or when spawned
void ADisplacer::BeginPlay()
{
	Super::BeginPlay();

	//Suscripción a los eventos de trigger enter
	boxCollider->OnComponentBeginOverlap.AddDynamic(this, &ADisplacer::TriggerEnter);

	//Suscripción a los eventos de trigger exit
	boxCollider->OnComponentEndOverlap.AddDynamic(this, &ADisplacer::TriggerExit);

	//Le pone la localización inicial en el Start
	this->SetActorLocation(Start->GetActorLocation());
}

void ADisplacer::SetWay(bool isBack, float DeltaTime) 
{
	//Hace el camino según que tipo de lado es al que va
	//Volviendo o no
	if (isBack) 
	{
		lerpProgress += displacementSpeed * DeltaTime;
	}

	else 
	{
		lerpProgress -= displacementSpeed * DeltaTime;
	}
}

// Called every frame
void ADisplacer::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	//Comprueba que la condición para moverse es correcta y que los puntos de inicio y final son reales
	if (bIsMoving == true && Start != nullptr && End != nullptr)
	{
		SetWay(bIsback, DeltaTime);
	}

	//Hace el vector de movimiento entre los dos puntos, adicionalmente el Clam se encarga de que el progreso del camino no salga de 0 a 100% hecho
	FVector MoveVector = FMath::Lerp(Start->GetActorLocation(), End->GetActorLocation(), FMath::Clamp(lerpProgress, 0.f, 1.f));

	if (lerpProgress >= 1)
		bIsback = false;

	else if (lerpProgress <= 0)
		bIsback = true;

	//Settea la localización al vector escalable de MoveVector
	this->SetActorRelativeLocation(MoveVector);
}

//Trigger enter
void ADisplacer::TriggerEnter(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Se hace un cast para comprobar que el Light es un Beacon
	ABeacon* Light = Cast<ABeacon>(OtherActor);

	//Si esa luz es un Beacon
	if (Light != nullptr)
	{
		//Para el Displacer
		bIsMoving = false;

		//Pide permiso para poder pasar el semaforo
		Light->LetDisplacerGoThrough(this);
	}
}

//Trigger exit
void ADisplacer::TriggerExit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//Se hace un cast para comprobar que el Light es un Beacon
	ABeacon* Light = Cast<ABeacon>(OtherActor);

	//Si esa luz es un Beacon
	if (Light != nullptr)
	{
		//Manda la señal al semaforo de que se ha ido y por tanto comienza el timer para poder dejar pasar a otro coche
		Light->LeavingCar();
	}
}



