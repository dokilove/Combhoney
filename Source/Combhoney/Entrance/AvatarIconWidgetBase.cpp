// Fill out your copyright notice in the Description page of Project Settings.

#include "AvatarIconWidgetBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Border.h"
#include "Kismet/GameplayStatics.h"
#include "Utilities/HttpService.h"

void UAvatarIconWidgetBase::NativeConstruct()
{
	Name = Cast<UTextBlock>(GetWidgetFromName("Name"));
	Level = Cast<UTextBlock>(GetWidgetFromName("Level"));
	Exp = Cast<UTextBlock>(GetWidgetFromName("Exp"));
	Equip1Info = Cast<UTextBlock>(GetWidgetFromName("Equip1Info"));
	Equip2Info = Cast<UTextBlock>(GetWidgetFromName("Equip2Info"));
	Equip3Info = Cast<UTextBlock>(GetWidgetFromName("Equip3Info"));
	ExpBar = Cast<UProgressBar>(GetWidgetFromName("ExpBar"));
	ItemButton= Cast<UButton>(GetWidgetFromName("IconButton"));
	OutBorder = Cast<UBorder>(GetWidgetFromName("OutBorder"));
	if (ItemButton)
	{
		ItemButton->OnClicked.AddDynamic(this, &UAvatarIconWidgetBase::SelectAvatar);
	}
}

void UAvatarIconWidgetBase::SelectAvatar()
{
}

void UAvatarIconWidgetBase::SetAvatarInfo(FAvatarInfo * AvatarInfo)
{
	if (Name)
	{
		Name->SetText(FText::FromString(*AvatarInfo->AvatarName));
	}
	if (Level)
	{
		Level->SetText(FText::FromString(FString::Printf(TEXT("%d"), AvatarInfo->Level)));
	}
	if (Exp)
	{
		Exp->SetText(FText::FromString(FString::Printf(TEXT("%d"), AvatarInfo->Exp)));
	}
	if (Equip1Info)
	{
		Equip1Info->SetText(FText::FromString(*AvatarInfo->EquipSlot1));
	}
	if (Equip2Info)
	{
		Equip2Info->SetText(FText::FromString(*AvatarInfo->EquipSlot2));
	}
	if (Equip3Info)
	{
		Equip3Info->SetText(FText::FromString(*AvatarInfo->EquipSlot3));
	}
}
