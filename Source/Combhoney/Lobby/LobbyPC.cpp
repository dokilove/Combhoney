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
	LobbyWidget = UMyStaticLibrary::MakeCustomWidget<ULobbyUserWidgetBase>(this, TEXT("WidgetBlueprint'/Game/Blueprints/Lobby/LobbyUserWidget.LobbyUserWidget_C'"), false);

	InventoryWidget = UMyStaticLibrary::MakeCustomWidget<UInventoryUserWidgetBase>(this,TEXT("WidgetBlueprint'/Game/Blueprints/Lobby/InventoryUserWidget.InventoryUserWidget_C'"));

	ShopWidget = UMyStaticLibrary::MakeCustomWidget<UShopUserWidgetBase>(this, TEXT("WidgetBlueprint'/Game/Blueprints/Lobby/ShopUserWidget.ShopUserWidget_C'"));

	bShowMouseCursor = true;
	SetInputMode(FInputModeGameAndUI());
}