// Fill out your copyright notice in the Description page of Project Settings.

#include "AvatarIconWidgetBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Border.h"
#include "Kismet/GameplayStatics.h"

void UAvatarIconWidgetBase::NativeConstruct()
{
	Name = Cast<UTextBlock>(GetWidgetFromName("Name"));
	Level = Cast<UTextBlock>(GetWidgetFromName("Level"));
	Exp = Cast<UTextBlock>(GetWidgetFromName("Exp"));
	Equip1 = Cast<UTextBlock>(GetWidgetFromName("Equip1Info"));
	Equip2 = Cast<UTextBlock>(GetWidgetFromName("Equip2Info"));
	Equip3 = Cast<UTextBlock>(GetWidgetFromName("Equip3Info"));
	ExpBar = Cast<UProgressBar>(GetWidgetFromName("ExpBar"));
	ItemButton= Cast<UButton>(GetWidgetFromName("Confirm"));
	OutBorder = Cast<UBorder>(GetWidgetFromName("OutBorder"));
	if (ItemButton)
	{
		ItemButton->OnClicked.AddDynamic(this, &UAvatarIconWidgetBase::SelectAvatar);
	}
}

void UAvatarIconWidgetBase::SelectAvatar()
{
}
