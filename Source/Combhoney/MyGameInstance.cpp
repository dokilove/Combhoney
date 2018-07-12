// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

void UMyGameInstance::Init()
{

}

void UMyGameInstance::SetAvatarInfo(TArray<FResponse_Login> AvatarInfo)
{
	MyAvatarInfo = AvatarInfo;


	for (auto LoginResponse : MyAvatarInfo)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d, %s, %d, %d, %s, %s, %s"), LoginResponse.avatarid, *LoginResponse.avatarname, LoginResponse.level, LoginResponse.exp, *LoginResponse.equipslot1, *LoginResponse.equipslot2, *LoginResponse.equipslot3);
	}
}
