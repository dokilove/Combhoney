// Fill out your copyright notice in the Description page of Project Settings.

#include "SetAvatarUserWidgetBase.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"
#include "Entrance/AvatarIconWidgetBase.h"
#include "Utilities/HttpService.h"
#include "Entrance/EntrancePC.h"

void USetAvatarUserWidgetBase::NativeConstruct()
{
	AccountName = Cast<UTextBlock>(GetWidgetFromName("AccountName"));

	AccountId = Cast<UTextBlock>(GetWidgetFromName("AccountId"));

	Gold = Cast<UTextBlock>(GetWidgetFromName("Gold"));

	Cash = Cast<UTextBlock>(GetWidgetFromName("Cash"));

	IconScrollBox = Cast<UScrollBox>(GetWidgetFromName("IconScrollBox"));
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

void USetAvatarUserWidgetBase::SetAvatarInfo(TArray<FAvatarInfo>* AvatarInfo)
{

	AEntrancePC* PC = Cast<AEntrancePC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (IconScrollBox && PC)
	{
		FStringClassReference IconRef(TEXT("WidgetBlueprint'/Game/Blueprints/Entrance/AvatarIconWidget.AvatarIconWidget_C'"));

		if (UClass* IconClass = IconRef.TryLoadClass<UUserWidget>())
		{
			for (int i = 0; i < (*AvatarInfo).Num(); ++i)
			{
				UAvatarIconWidgetBase* Icon = CreateWidget<UAvatarIconWidgetBase>(PC, IconClass);
				Icon->SetAvatarUserWidget(this);
				Icon->SetAvatarInfo(&(*AvatarInfo)[i]);
				IconScrollBox->AddChild(Icon);

			}
		}
	}
}

void USetAvatarUserWidgetBase::SelectAvatar(UAvatarIconWidgetBase * AvatarIcon)
{
	SelectedAvatar = AvatarIcon->IconAvatarInfo;
	for (int i = 0; i < IconScrollBox->GetChildrenCount(); ++i)
	{
		UAvatarIconWidgetBase* Icon = Cast<UAvatarIconWidgetBase>(IconScrollBox->GetChildAt(i));
		if (AvatarIcon == Icon)
		{
			Icon->Selected();
		}
		else
		{
			Icon->Deselected();
		}
	}
}