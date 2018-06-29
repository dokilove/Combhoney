// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyPC.h"
#include "Lobby/LobbyUserWidgetBase.h"
#include "Lobby/InventoryUserWidgetBase.h"
#include "Lobby/ShopUserWidgetBase.h"

void ALobbyPC::BeginPlay()
{
	SetupWidget();
}

void ALobbyPC::SetupWidget()
{
	LobbyWidget = Cast<ULobbyUserWidgetBase>(MakeWidget(TEXT("WidgetBlueprint'/Game/Blueprints/Lobby/LobbyUserWidget.LobbyUserWidget_C'")));

	InventoryWidget = Cast<UInventoryUserWidgetBase>(MakeWidget(TEXT("WidgetBlueprint'/Game/Blueprints/Lobby/InventoryUserWidget.InventoryUserWidget_C'")));

	ShopWidget = Cast<UShopUserWidgetBase>(MakeWidget(TEXT("WidgetBlueprint'/Game/Blueprints/Lobby/ShopUserWidget.ShopUserWidget_C'")));
}

UUserWidget* ALobbyPC::MakeWidget(FString path)
{
	UUserWidget* ResultWidget = nullptr;
	FStringClassReference WidgetRef(path);
	if (UClass* WidgetClass = WidgetRef.TryLoadClass<UUserWidget>())
	{
		ResultWidget = CreateWidget<UUserWidget>(this, WidgetClass);
		ResultWidget->AddToViewport();
	}
	return ResultWidget;
}
