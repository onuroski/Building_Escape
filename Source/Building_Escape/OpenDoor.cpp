// Copyright Onur Sağaltıcı 2023


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;
	
}
	bool bOpenDoor = true; // Declare the variable bOpenDoor

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{


	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//print the name of the actor that opens the door once
	if (PressurePlate->IsOverlappingActor(ActorThatOpens) && bOpenDoor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor %s is in the trigger volume"), *ActorThatOpens->GetName());
		bOpenDoor = false;
	}
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);	
	}
	//destroy the actor after opening door completed
	if (CurrentYaw >= TargetYaw)
	{
		ActorThatOpens->Destroy();
	}
	
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), GetOwner()->GetActorRotation().Yaw);

	CurrentYaw = FMath::FInterpConstantTo(CurrentYaw, TargetYaw, DeltaTime, 30);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}
