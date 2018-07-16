// Fill out your copyright notice in the Description page of Project Settings.

#include "EntrancePC.h"
#include "Entrance/EntranceWidgetBase.h"
#include "Entrance/RegisterWidgetBase.h"
#include "Entrance/SetAvatarUserWidgetBase.h"
#include "MyStatic/MyStaticLibrary.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"

void AEntrancePC::BeginPlay()
{
	EntranceWidget = UMyStaticLibrary::MakeCustomWidget<UEntranceWidgetBase>(this, TEXT("WidgetBlueprint'/Game/Blueprints/Entrance/EntranceWidget.EntranceWidget_C'"), false);

	MenuMap.Add(EEntranceMenuState::Entrance, EntranceWidget);

	RegisterWidget = UMyStaticLibrary::MakeCustomWidget<URegisterWidgetBase>(this, TEXT("WidgetBlueprint'/Game/Blueprints/Entrance/RegisterWidget.RegisterWidget_C'"));

	MenuMap.Add(EEntranceMenuState::Register, RegisterWidget);

	SetAvatarWidget = UMyStaticLibrary::MakeCustomWidget<USetAvatarUserWidgetBase>(this, TEXT("WidgetBlueprint'/Game/Blueprints/Entrance/SetAvatarWidget.SetAvatarWidget_C'"));

	MenuMap.Add(EEntranceMenuState::SetAvatar, SetAvatarWidget);

	bShowMouseCursor = true;
	SetInputMode(FInputModeUIOnly());

	EntranceWidget->AccountID->SetUserFocus(this);
}

void AEntrancePC::LoginSuccess(FAccountInfo AccountInfo)
{
	UMyGameInstance* GI = Cast<UMyGameInstance>(
		UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		GI->SetAccountInfo(AccountInfo);

		SetAvatarWidget->SetAccountInfo();


		AHttpService* HttpService = UMyStaticLibrary::GetHttpService(this);
		if (HttpService != nullptr)
		{
			HttpService->AllAvatarInfo(GI->MyAccountInfo.Idx, this);
		}
	}

}

void AEntrancePC::AllAvatarInfoSuccess(TArray<struct FAvatarInfo> AvatarInfos)
{
	UMyGameInstance* GI = Cast<UMyGameInstance>(
		UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		GI->SetAvatarInfo(AvatarInfos);
		OpenMenu(EEntranceMenuState::SetAvatar);
	}
}

void AEntrancePC::OpenMenu(EEntranceMenuState Menu)
{
	for (auto Widget : MenuMap)
	{
		if (Widget.Key == Menu)
		{
			continue;
		}
		Widget.Value->SetVisibility(ESlateVisibility::Collapsed);
	}
	MenuMap[Menu]->SetVisibility(ESlateVisibility::Visible);
}
