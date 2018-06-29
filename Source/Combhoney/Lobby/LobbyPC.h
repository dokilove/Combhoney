// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPC.generated.h"

/**
 * 
 */
UCLASS()
class COMBHONEY_API ALobbyPC : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	void SetupWidget();

	UUserWidget* MakeWidget(FString path);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ULobbyUserWidgetBase* LobbyWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UInventoryUserWidgetBase* InventoryWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UShopUserWidgetBase* ShopWidget;
};
