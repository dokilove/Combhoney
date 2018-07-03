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
		FString id;
	UPROPERTY()
		FString nickname;
	UPROPERTY()
		FString password;

	FRequest_Register() {}
};

USTRUCT()
struct FResponse_Register {
	GENERATED_BODY()
		UPROPERTY()
		FString Log;

	FResponse_Register() {}
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

	void Register(FRequest_Register RegisterInfo);
	void RegisterResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

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
