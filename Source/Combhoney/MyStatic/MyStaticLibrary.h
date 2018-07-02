// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyStaticLibrary.generated.h"

/**
 * 
 */
UCLASS()
class COMBHONEY_API UMyStaticLibrary : public UObject
{
	GENERATED_BODY()
	
public:
	static class UUserWidget* MakeUserWidget(APlayerController* PC, FString path, bool bIsCollapsed = true);
	
	template <class T>
	static T* MakeCustomWidget(APlayerController* PC, FString path, bool bIsCollapesd = true)
	{
		return Cast<T>(MakeUserWidget(PC, path, bIsCollapesd));
	}
};
