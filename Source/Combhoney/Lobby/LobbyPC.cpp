// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyPC.h"
#include "Lobby/LobbyUserWidgetBase.h"
#include "Lobby/InventoryUserWidgetBase.h"
#include "Lobby/ShopUserWidgetBase.h"
#include "MyStatic/MyStaticLibrary.h"

void ALobbyPC::BeginPlay()
{
	SetupWidget();
}

void ALobbyPC::SetupWidget()
{
	LobbyWidget = Cast<ULobbyUserWidgetBase>(UMyStaticLibrary::MakeWidget(this, TEXT("WidgetBlueprint'/Game/Blueprints/Lobby/LobbyUserWidget.LobbyUserWidget_C'"), false));

	InventoryWidget = Cast<UInventoryUserWidgetBase>(UMyStaticLibrary::MakeWidget(this,TEXT("WidgetBlueprint'/Game/Blueprints/Lobby/InventoryUserWidget.InventoryUserWidget_C'")));

	ShopWidget = Cast<UShopUserWidgetBase>(UMyStaticLibrary::MakeWidget(this, TEXT("WidgetBlueprint'/Game/Blueprints/Lobby/ShopUserWidget.ShopUserWidget_C'")));

	bShowMouseCursor = true;
	SetInputMode(FInputModeGameAndUI());
}