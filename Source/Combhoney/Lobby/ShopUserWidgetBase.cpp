// Fill out your copyright notice in the Description page of Project Settings.

#include "ShopUserWidgetBase.h"
#include "Lobby/SubMenuBarUserWidgetBase.h"

void UShopUserWidgetBase::NativeConstruct()
{
	SubMenuBar = Cast<USubMenuBarUserWidgetBase>(GetWidgetFromName("SubMenuBarUserWidget"));
}




