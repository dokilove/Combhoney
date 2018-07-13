// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EntrancePC.generated.h"

/**
 * 
 */
UCLASS()
class COMBHONEY_API AEntrancePC : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UEntranceWidgetBase* EntranceWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class URegisterWidgetBase* RegisterWidget;	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USetAvatarUserWidgetBase* SetAvatarWidget;

	void LoginSuccess(struct FAccountInfo AccountInfo);
};
