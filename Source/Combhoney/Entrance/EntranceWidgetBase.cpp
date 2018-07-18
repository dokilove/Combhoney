// Fill out your copyright notice in the Description page of Project Settings.

#include "EntranceWidgetBase.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Utilities/HttpService.h"
#include "MyStatic/MyStaticLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Entrance/EntrancePC.h"

void UEntranceWidgetBase::NativeConstruct()
{
	AccountID = Cast<UEditableTextBox>(GetWidgetFromName("accountid"));
	Password = Cast<UEditableTextBox>(GetWidgetFromName("password"));
	RegisterButton = Cast<UButton>(GetWidgetFromName("register"));
	if (RegisterButton)
	{
		RegisterButton->OnClicked.AddDynamic(this, &UEntranceWidgetBase::Register);
	}
	LoginButton = Cast<UButton>(GetWidgetFromName("login"));
	if (LoginButton)
	{
		LoginButton->OnClicked.AddDynamic(this, &UEntranceWidgetBase::Login);
	}
}

void UEntranceWidgetBase::Register()
{
	UE_LOG(LogClass, Warning, TEXT("Register Action"));

	AEntrancePC* PC = Cast<AEntrancePC>(
		UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->OpenMenu(EEntranceMenuState::Register);
	}
}

void UEntranceWidgetBase::Login()
{
	UE_LOG(LogClass, Warning, TEXT("Login Action"));

	if (AccountID && Password)
	{
		if (AccountID->GetText().ToString().Len() > 0 && Password->GetText().ToString().Len() > 0)
		{

			FRequest_Login LoginInfo;
			LoginInfo.accountid = AccountID->GetText().ToString();
			LoginInfo.password = Password->GetText().ToString();


			AEntrancePC* PC = Cast<AEntrancePC>(
				UGameplayStatics::GetPlayerController(GetWorld(), 0));
			if (PC)
			{
				AHttpService* HttpService = UMyStaticLibrary::GetHttpService(PC);
				if (HttpService != nullptr)
				{
					HttpService->Login(LoginInfo, PC);
				}
			}
			else
			{
				UE_LOG(LogClass, Warning, TEXT("http service is nullptr"));
			}
		}
	}
}

ESlateVisibility UEntranceWidgetBase::FocusToAccountID()
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

void UEntranceWidgetBase::ResetInfo()
{
	if (AccountID)
	{
		AccountID->SetText(FText());
	}
	if (Password)
	{
		Password->SetText(FText());
	}
}


