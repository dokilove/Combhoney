// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EntranceWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class COMBHONEY_API UEntranceWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UEditableTextBox* AccountID;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UEditableTextBox* Password;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UButton* RegisterButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UButton* LoginButton;

	UFUNCTION()
		void Register();
	UFUNCTION()
		void Login();
};
