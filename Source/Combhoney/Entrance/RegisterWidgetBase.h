// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RegisterWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class COMBHONEY_API URegisterWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UEditableTextBox* AccountID;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UEditableTextBox* NickName;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UEditableTextBox* Password;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UEditableTextBox* PasswordAgain;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextBlock* Notice;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UButton* RegisterButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UButton* BackButton;
	UFUNCTION()
	void Register();
	UFUNCTION()
	void Back();
	UFUNCTION()
		ESlateVisibility FocusToAccountID();

	void ResetInfo();
	UFUNCTION()
	void OnTextChanged(const FText & Text);
};
