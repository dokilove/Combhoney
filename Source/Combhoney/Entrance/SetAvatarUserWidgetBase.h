// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SetAvatarUserWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class COMBHONEY_API USetAvatarUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextBlock* AccountName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextBlock* AccountId;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextBlock* Gold;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextBlock* Cash;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UScrollBox* IconScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UButton* CreateAvatarButton;
	UFUNCTION()
	void CreateAvatar();

	void SetAccountInfo();

	void SetAvatarInfo(TArray<struct FAvatarInfo>* AvatarInfo);

	void SelectAvatar(class UAvatarIconWidgetBase* AvatarIcon);

	struct FAvatarInfo* SelectedAvatar;

	void ClearAvatarScroll();
};
