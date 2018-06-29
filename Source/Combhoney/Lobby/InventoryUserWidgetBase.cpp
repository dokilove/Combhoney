// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryUserWidgetBase.h"
#include "Lobby/SubMenuBarUserWidgetBase.h"

void UInventoryUserWidgetBase::NativeConstruct()
{
	SubMenuBar = Cast<USubMenuBarUserWidgetBase>(GetWidgetFromName("SubMenuBarUserWidget"));
}


