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
}

void UEntranceWidgetBase::Login()
{
	UE_LOG(LogClass, Warning, TEXT("Login Action"));

	if (AccountID && Password)
	{
		FRequest_Login LoginInfo;
		LoginInfo.accountid = AccountID->GetText().ToString();
		LoginInfo.password = Password->GetText().ToString();

		AHttpService* HttpService = UMyStaticLibrary::GetHttpService(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (HttpService != nullptr)
		{
			//TArray <FResponse_Login> LoginResponses;

			//HttpService->Login(LoginInfo, &LoginResponses);

			//for (auto LoginResponse : LoginResponses)
			//{
			//	UE_LOG(LogTemp, Warning, TEXT("%d, %s, %d, %d, %s, %s, %s"), LoginResponse.avatarid, *LoginResponse.avatarname, LoginResponse.level, LoginResponse.exp, *LoginResponse.equipslot1, *LoginResponse.equipslot2, *LoginResponse.equipslot3);
			//}

			AEntrancePC* PC = Cast<AEntrancePC>(
				UGameplayStatics::GetPlayerController(GetWorld(), 0));
			if (PC)
			{
				//GI->SetAvatarInfo(LoginResponses);
				HttpService->Login(LoginInfo, PC);
			}

			
		}
		else
		{
			UE_LOG(LogClass, Warning, TEXT("http service is nullptr"));
		}
	}
}


