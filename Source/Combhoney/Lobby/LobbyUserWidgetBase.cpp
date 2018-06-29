// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyUserWidgetBase.h"
#include "Components/Button.h"

void ULobbyUserWidgetBase::NativeConstruct()
{
	InventoryButton = Cast<UButton>(GetWidgetFromName("Inventory"));
	if (InventoryButton) 
	{
		InventoryButton->OnClicked.AddDynamic(this, &ULobbyUserWidgetBase::Inventory);
	}
	ShopButton = Cast<UButton>(GetWidgetFromName("Shop"));
	if (ShopButton)
	{
		ShopButton->OnClicked.AddDynamic(this, &ULobbyUserWidgetBase::Shop);
	}
}

void ULobbyUserWidgetBase::Inventory()
{

}

void ULobbyUserWidgetBase::Shop()
{

}