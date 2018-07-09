// Fill out your copyright notice in the Description page of Project Settings.

#include "EntrancePC.h"
#include "Entrance/EntranceWidgetBase.h"
#include "Entrance/RegisterWidgetBase.h"
#include "MyStatic/MyStaticLibrary.h"

void AEntrancePC::BeginPlay()
{
	EntranceWidget = UMyStaticLibrary::MakeCustomWidget<UEntranceWidgetBase>(this, TEXT("WidgetBlueprint'/Game/Blueprints/Entrance/EntranceWidget.EntranceWidget_C'"), false);

	bShowMouseCursor = true;
	SetInputMode(FInputModeUIOnly());
}



