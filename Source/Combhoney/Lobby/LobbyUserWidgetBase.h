// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyUserWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class COMBHONEY_API ULobbyUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UButton* InventoryButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UButton* ShopButton;
	UFUNCTION()
	void Inventory();
	UFUNCTION()
	void Shop();
};
