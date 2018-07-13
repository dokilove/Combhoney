// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Utilities/HttpService.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class COMBHONEY_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	UPROPERTY()
		FAccountInfo MyAccountInfo;

	UPROPERTY()
		TArray<FAvatarInfo> MyAvatarInfo;
	
	void SetAccountInfo(FAccountInfo AccountInfo);
	void SetAvatarInfo(TArray<FAvatarInfo> AvatarInfo);
};
