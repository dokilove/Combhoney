// Fill out your copyright notice in the Description page of Project Settings.

#include "MyStaticLibrary.h"
#include "UserWidget.h"
#include "GameFramework/PlayerController.h"

class UUserWidget* UMyStaticLibrary::MakeWidget(APlayerController* PC, FString path, bool bIsCollapsed)
{
	UUserWidget* ResultWidget = nullptr;
	FStringClassReference WidgetRef(path);
	if (UClass* WidgetClass = WidgetRef.TryLoadClass<UUserWidget>())
	{
		ResultWidget = CreateWidget<UUserWidget>(PC, WidgetClass);
		ResultWidget->AddToViewport();
		if (bIsCollapsed)
		{
			ResultWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			ResultWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
	return ResultWidget;
}


