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

	SetAvatarWidget = UMyStaticLibrary::MakeCustomWidget<USetAvatarUserWidgetBase>(this, TEXT("WidgetBlueprint'/Game/Blueprints/Entrance/SetAvatarWidget.SetAvatarWidget_C'"));

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
			HttpService->AllAvatarInfo(GI->AccountIdx, this);
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
		
		EntranceWidget->SetVisibility(ESlateVisibility::Collapsed);
		SetAvatarWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
