// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

void UMyGameInstance::Init()
{

}

void UMyGameInstance::SetAvatarInfo(TArray<FAvatarInfo> AvatarInfo)
{
	MyAvatarInfo = AvatarInfo;

	for (auto LoginResponse : MyAvatarInfo)
	{
		UE_LOG(LogTemp, Warning, TEXT("GI %d, %s, %d, %d, %s, %s, %s"), LoginResponse.AvatarId, *LoginResponse.AvatarName, LoginResponse.Level, LoginResponse.Exp, *LoginResponse.EquipSlot1, *LoginResponse.EquipSlot2, *LoginResponse.EquipSlot3);
	}
}
