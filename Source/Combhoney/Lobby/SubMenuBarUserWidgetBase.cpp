// Fill out your copyright notice in the Description page of Project Settings.

#include "SubMenuBarUserWidgetBase.h"
#include "Components/Button.h"

void USubMenuBarUserWidgetBase::NativeConstruct()
{
	BackButton = Cast<UButton>(GetWidgetFromName("Back"));
	if (BackButton) 
	{
		BackButton->OnClicked.AddDynamic(this, &USubMenuBarUserWidgetBase::Back);
	}
}

void USubMenuBarUserWidgetBase::Back()
{

}