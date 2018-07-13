// Fill out your copyright notice in the Description page of Project Settings.

#include "SetAvatarUserWidgetBase.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"

void USetAvatarUserWidgetBase::NativeConstruct()
{
	AccountName = Cast<UTextBlock>(GetWidgetFromName("AccountName"));

	AccountId = Cast<UTextBlock>(GetWidgetFromName("AccountId"));

	Gold = Cast<UTextBlock>(GetWidgetFromName("Gold"));

	Cash = Cast<UTextBlock>(GetWidgetFromName("Cash"));
}

void USetAvatarUserWidgetBase::SetAccountInfo()
{
	UMyGameInstance* GI = Cast<UMyGameInstance>(
		UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		if (AccountName)
		{
			AccountName->SetText(FText::FromString(*GI->MyAccountInfo.AccountName));
		}
		if (AccountId)
		{
			AccountId->SetText(FText::FromString(*GI->MyAccountInfo.AccountId));
		}
		if (Gold)
		{
			Gold->SetText(FText::FromString(FString::Printf(TEXT("Gold : %d"), GI->MyAccountInfo.Gold)));
		}
		if (Cash)
		{
			Cash->SetText(FText::FromString(FString::Printf(TEXT("Cash: %d"), GI->MyAccountInfo.Cash)));
		}
	}
}
