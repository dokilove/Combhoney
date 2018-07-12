﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "EntranceWidgetBase.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Utilities/HttpService.h"
#include "MyStatic/MyStaticLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"

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
}

void UEntranceWidgetBase::Login()
{
	UE_LOG(LogClass, Warning, TEXT("Login Action"));

	if (AccountID && Password)
	{
		FRequest_Login LoginInfo;
		LoginInfo.accountid = AccountID->GetText().ToString();
		LoginInfo.password = Password->GetText().ToString();
		// 어떻게든 HTTP 불러서 만들것
		TArray <FResponse_Login> LoginResponses;
		AHttpService* HttpService = UMyStaticLibrary::GetHttpService(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (HttpService != nullptr)
		{
			HttpService->Login(LoginInfo, &LoginResponses);

			UMyGameInstance* GI = Cast<UMyGameInstance>(
				UGameplayStatics::GetGameInstance(GetWorld()));
			if (GI)
			{
				GI->SetAvatarInfo(LoginResponses);
			}
		}
		else
		{
			UE_LOG(LogClass, Warning, TEXT("http service is nullptr"));
		}
	}
}


