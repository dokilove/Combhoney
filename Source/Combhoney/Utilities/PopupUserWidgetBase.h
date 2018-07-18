// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PopupUserWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class COMBHONEY_API UPopupUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextBlock* Message;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UButton* ConfirmButton;
	UFUNCTION()
	void ClosePopup();

	void SetMessage(FString MessageString);
};
