// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "HttpService.generated.h"

USTRUCT()
struct FRequest_Register {
	GENERATED_BODY()
		UPROPERTY()
		FString accountid;
	UPROPERTY()
		FString accountname;
	UPROPERTY()
		FString password;

	FRequest_Register() {}
};

USTRUCT()
struct FAccountInfo {
	GENERATED_BODY()
public:	
	UPROPERTY()
		int32 Idx;
	UPROPERTY()
		FString AccountId;
	UPROPERTY()
		FString AccountName;
	UPROPERTY()
		int32 Gold;
	UPROPERTY()
		int32 Cash;
	FAccountInfo() {}
};

USTRUCT()
struct FRequest_Login {
	GENERATED_BODY()

public:
	UPROPERTY()
		FString accountid;
	UPROPERTY()
		FString password;
	FRequest_Login() {}
};

USTRUCT()
struct FAvatarInfo {
	GENERATED_BODY()
public:
	UPROPERTY()
		int32 AvatarId;
	UPROPERTY()
		FString  AvatarName;
	UPROPERTY()
		int32 Level;
	UPROPERTY()
		int32  Exp;
	UPROPERTY()
		FString  EquipSlot1;
	UPROPERTY()
		FString  EquipSlot2;
	UPROPERTY()
		FString  EquipSlot3;
	FAvatarInfo() {}
};

USTRUCT()
struct FRequest_AccountIdx {
	GENERATED_BODY()
public:
	UPROPERTY()
		int32 Idx;
	FRequest_AccountIdx() {}
};

UCLASS(Blueprintable, hideCategories = (Rendering, Replication, Input, Actor, "Actor Tick"))
class COMBHONEY_API AHttpService : public AActor
{
	GENERATED_BODY()

private:
	FHttpModule* Http;
	FString ApiBaseURl = "http://localhost:8000";

	FString AuthorizationHeader = TEXT("Authorization");
	void SetAuthorizationHash(FString Hash, TSharedRef<IHttpRequest>& Request);

	TSharedRef<IHttpRequest> RequestWithRoute(FString Subroute);
	void SetRequestHeaders(TSharedRef<IHttpRequest>& Request);

	TSharedRef<IHttpRequest> GetRequest(FString Subroute);
	TSharedRef<IHttpRequest> PostRequest(FString Subroute, FString ContentJsonString);
	void Send(TSharedRef<IHttpRequest>& Request);

	bool ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful);

	template<typename StructType>
	void GetJsonStringFromStruct(StructType FilledStruct, FString& StringOutput);
	template<typename StructType>
	void GetStructFromJsonString(FHttpResponsePtr Response, StructType& StructOutput);
	
public:	
	// Sets default values for this actor's properties
	AHttpService();

	void Register(FRequest_Register RegisterInfo, class AEntrancePC* PC);
	void RegisterResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, class AEntrancePC* PC);

	void Login(FRequest_Login LoginInfo, class AEntrancePC* PC);
	void LoginResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, class AEntrancePC* PC);

	void AllAvatarInfo(int32 Idx, class AEntrancePC* PC);
	void AllAvatarInfoResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, class AEntrancePC* PC);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};

template<typename StructType>
inline void AHttpService::GetJsonStringFromStruct(StructType FilledStruct, FString & StringOutput)
{
	FJsonObjectConverter::UStructToJsonObjectString(StructType::StaticStruct(), &FilledStruct, StringOutput, 0, 0);
}

template<typename StructType>
inline void AHttpService::GetStructFromJsonString(FHttpResponsePtr Response, StructType & StructOutput)
{
	StructType StructData;
	FString JsonString = Response->GetContentAsString();
	FJsonObjectConverter::JsonObjectStringToUStruct<StructType>(JsonString, &StructOutput, 0, 0);
}

template<typename StructType>
inline void AHttpService::GetStructFromJsonStringArray(FHttpResponsePtr Response, TArray<StructType>& StructArray)
{
	FString JsonString = Response->GetContentAsString();
	FJsonObjectConverter::JsonArrayStringToUStruct(JsonString, &StructArray, 0, 0);
}