// Fill out your copyright notice in the Description page of Project Settings.

#include "MyStaticLibrary.h"
#include "UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Utilities/HttpService.h"

class UUserWidget* UMyStaticLibrary::MakeUserWidget(APlayerController* PC, FString path, bool bIsCollapsed)
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

AHttpService * UMyStaticLibrary::GetHttpService()
{
	AHttpService* HttpService = nullptr;

	FStringClassReference HttpRef(TEXT("Blueprint'/Game/Blueprints/Utilities/BP_Http.BP_Http_C'"));
	if (UClass* HttpClass = HttpRef.TryLoadClass<AHttpService>())
	{
		//HttpService = Cast<AHttpService>(HttpClass);
		UE_LOG(LogClass, Warning, TEXT("http service load succeed"));
	}

	if (HttpService == nullptr)
	{
		UE_LOG(LogClass, Warning, TEXT("http service load succeed but null"));
	}

	return HttpService;
}
