// Fill out your copyright notice in the Description page of Project Settings.

#include "PopupUserWidgetBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UPopupUserWidgetBase::NativeConstruct()
{
	Message = Cast<UTextBlock>(GetWidgetFromName("Message"));

	ConfirmButton = Cast<UButton>(GetWidgetFromName("Confirm"));
	if (ConfirmButton)
	{
		ConfirmButton->OnClicked.AddDynamic(this, &UPopupUserWidgetBase::ClosePopup);
	}
}

void UPopupUserWidgetBase::ClosePopup()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UPopupUserWidgetBase::SetMessage(FString MessageString)
{
	if (Message)
	{
		Message->SetText(FText::FromString(MessageString));
	}
	if (ConfirmButton)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		if (PC)
		{
			ConfirmButton->SetUserFocus(PC);
		}
	}
}
