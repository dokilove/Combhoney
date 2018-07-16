// Fill out your copyright notice in the Description page of Project Settings.

#include "RegisterWidgetBase.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void URegisterWidgetBase::NativeConstruct()
{
	AccountID = Cast<UEditableTextBox>(GetWidgetFromName("AccountId"));
	NickName = Cast<UEditableTextBox>(GetWidgetFromName("NickName"));
	Password = Cast<UEditableTextBox>(GetWidgetFromName("Password"));
	PasswordAgain = Cast<UEditableTextBox>(GetWidgetFromName("PasswordAgain"));

	Notice = Cast<UTextBlock>(GetWidgetFromName("Notice"));

	RegisterButton = Cast<UButton>(GetWidgetFromName("RegisterButton"));
	if (RegisterButton)
	{
		RegisterButton->OnClicked.AddDynamic(this, &URegisterWidgetBase::Register);
	}
	BackButton = Cast<UButton>(GetWidgetFromName("BackButton"));
	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &URegisterWidgetBase::Back);
	}
}

void URegisterWidgetBase::Register()
{

}

void URegisterWidgetBase::Back()
{

}