// Fill out your copyright notice in the Description page of Project Settings.

#include "Escape.h"
#include "DoorOpener.h"


// Sets default values for this component's properties
UDoorOpener::UDoorOpener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();
}

void UDoorOpener::OpenDoor()
{
	Owner->SetActorRelativeRotation(OpenRotation);
	LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	IsDoorOpen = true;
}

void UDoorOpener::CloseDoor()
{
	Owner->SetActorRelativeRotation(ClosedRotation);
	IsDoorOpen = false;
}


// Called every frame
void UDoorOpener::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
	}
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) {
		CloseDoor();
	}
}

