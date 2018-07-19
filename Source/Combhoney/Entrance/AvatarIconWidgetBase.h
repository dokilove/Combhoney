// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AvatarIconWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class COMBHONEY_API UAvatarIconWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	

public:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextBlock* Name;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextBlock* Level;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextBlock* Exp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextBlock* Equip1Info;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextBlock* Equip2Info;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UTextBlock* Equip3Info;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UButton* ItemButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UProgressBar* ExpBar;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBorder* OutBorder;
	UFUNCTION()
		void SelectAvatar();

	void SetAvatarInfo(struct FAvatarInfo* AvatarInfo);
	struct FAvatarInfo* IconAvatarInfo;

	void SetAvatarUserWidget(class USetAvatarUserWidgetBase*UserWidget);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USetAvatarUserWidgetBase* AvatarUserWidget;
	
	void Selected();
	void Deselected();
};
