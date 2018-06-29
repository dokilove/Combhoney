// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGM.h"
#include "UObject/ConstructorHelpers.h"
#include "Lobby/LobbyPC.h"

ALobbyGM::ALobbyGM()
{
	static ConstructorHelpers::FClassFinder<ALobbyPC> PC_Class(TEXT("Blueprint'/Game/Blueprints/Lobby/BP_LobbyPC.BP_LobbyPC_C'"));
	if (PC_Class.Succeeded())
	{
		PlayerControllerClass = PC_Class.Class;
	}
}


