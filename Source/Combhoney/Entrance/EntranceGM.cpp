// Fill out your copyright notice in the Description page of Project Settings.

#include "EntranceGM.h"
#include "UObject/ConstructorHelpers.h"
#include "Entrance/EntrancePC.h"

AEntranceGM::AEntranceGM()
{
	static ConstructorHelpers::FClassFinder<AEntrancePC> PC_Class(TEXT("Blueprint'/Game/Blueprints/Entrance/BP_EntrancePC.BP_EntrancePC_C'"));
	if (PC_Class.Succeeded())
	{
		PlayerControllerClass = PC_Class.Class;
	}
}


