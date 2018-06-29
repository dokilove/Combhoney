// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SubMenuBarUserWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class COMBHONEY_API USubMenuBarUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UButton* BackButton;
	UFUNCTION()
	void Back();

};
