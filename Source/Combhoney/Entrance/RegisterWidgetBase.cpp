// Fill out your copyright notice in the Description page of Project Settings.

#include "RegisterWidgetBase.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Entrance/EntrancePC.h"
#include "Kismet/GameplayStatics.h"

void URegisterWidgetBase::NativeConstruct()
{
	AccountID = Cast<UEditableTextBox>(GetWidgetFromName("AccountId"));

	NickName = Cast<UEditableTextBox>(GetWidgetFromName("NickName"));
	Password = Cast<UEditableTextBox>(GetWidgetFromName("Password"));
	Password->OnTextChanged.AddDynamic(this, &URegisterWidgetBase::OnTextChanged);
	PasswordAgain = Cast<UEditableTextBox>(GetWidgetFromName("PasswordAgain"));
	PasswordAgain->OnTextChanged.AddDynamic(this, &URegisterWidgetBase::OnTextChanged);

	Notice = Cast<UTextBlock>(GetWidgetFromName("Notice"));

	RegisterButton = Cast<UButton>(GetWidgetFromName("RegisterButton"));
	if (RegisterButton)
	{
		RegisterButton->OnClicked.AddDynamic(this, &URegisterWidgetBase::Register);
	}
	BackButton = Cast<UButton>(GetWidgetFromName("BackButton"));
	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &URegisterWidgetBase::Back);
	}
}

void URegisterWidgetBase::Register()
{

}

void URegisterWidgetBase::Back()
{
	AEntrancePC* PC = Cast<AEntrancePC>(
		UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->OpenMenu(EEntranceMenuState::Entrance);
	}
}

ESlateVisibility URegisterWidgetBase::FocusToAccountID()
{
	AEntrancePC* PC = Cast<AEntrancePC>(
		UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC && AccountID)
	{
		ResetInfo();
		AccountID->SetUserFocus(PC);
	}

	return ESlateVisibility::Visible;
}

void URegisterWidgetBase::ResetInfo()
{
	if (AccountID)
	{
		AccountID->SetText(FText());
	}
	if (NickName)
	{
		NickName->SetText(FText());
	}
	if (Password)
	{
		Password->SetText(FText());
	}
	if (PasswordAgain)
	{
		PasswordAgain->SetText(FText());
	}
}

void URegisterWidgetBase::OnTextChanged(const FText& Text)
{
	FString PasswordString = Password->GetText().ToString();
	FString PasswordAgainString = Text.ToString();


	for (int i = 0; i < PasswordAgainString.Len(); ++i)
	{
		if (!PasswordString.IsEmpty() && PasswordString.Len() > i)
		{
			if (PasswordString[i] != PasswordAgainString[i])
			{
				Notice->SetText(FText::FromString(TEXT("Password 일치 하지 않음")));
				break;
			}
			else {
				Notice->SetText(FText::FromString(TEXT("....")));
			}
		}
		else
		{
			Notice->SetText(FText::FromString(TEXT("Password 범위 벗어남")));
			break;
		}
	}
}