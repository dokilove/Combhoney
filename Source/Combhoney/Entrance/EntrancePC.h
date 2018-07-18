// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EntrancePC.generated.h"

UENUM(BlueprintType)
enum class EEntranceMenuState : uint8
{
	Entrance UMETA(Display = "Entrance"),
	Register UMETA(Display = "Register"),
	SetAvatar UMETA(Display = "SetAvatar"),
};

/**
 * 
 */
UCLASS()
class COMBHONEY_API AEntrancePC : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UPROPERTY(Category = Const, EditAnywhere)
		TMap<EEntranceMenuState, UUserWidget*> MenuMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UEntranceWidgetBase* EntranceWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class URegisterWidgetBase* RegisterWidget;	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USetAvatarUserWidgetBase* SetAvatarWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UPopupUserWidgetBase* PopupWidget;


	void RegistSuccess(struct FAccountInfo AccountInfo);
	void LoginSuccess(struct FAccountInfo AccountInfo);
	void AllAvatarInfoSuccess(TArray<struct FAvatarInfo> AvatarInfos);
	
	void OpenMenu(EEntranceMenuState Menu);

	void OpenPopup(FString Message);
};
