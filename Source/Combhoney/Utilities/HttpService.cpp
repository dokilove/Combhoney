﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "HttpService.h"
#include "Entrance/EntrancePC.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Tables/ErrorLogComponent.h"

// Sets default values
AHttpService::AHttpService()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ErrorLogTable = CreateDefaultSubobject<UErrorLogComponent>(TEXT("ErrorLogTable"));
}

bool AHttpService::IsSuccess(FHttpResponsePtr Response)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	// 에러코드에는 head를 왜
	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject->HasField("errorCode"))
	{
		int ErrorCode = (int)JsonObject->GetNumberField(TEXT("errorCode"));
		
		FString ErrorLog = ErrorLogTable->GetErrorLogData(ErrorCode).Desc;
		UMyGameInstance* GI = Cast<UMyGameInstance>(
			UGameplayStatics::GetGameInstance(GetWorld()));
		if (GI)
		{
			GI->PopupMessage.ExecuteIfBound(ErrorLog);
		}

		UE_LOG(LogClass, Warning, TEXT("Error code : %s\n"), *ErrorLog);

		return false;
	}

	return true;
}

void AHttpService::Register(FRequest_Register RegisterInfo, class AEntrancePC* PC)
{
	FString ContentJsonString;
	GetJsonStringFromStruct<FRequest_Register>(RegisterInfo, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("/register", ContentJsonString);
	//TSharedRef<IHttpRequest> Request = PostRequest("/login", ContentJsonString);
	//TSharedRef<IHttpRequest> Request = GetRequest("/login");
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::RegisterResponse, PC);
	Send(Request);
}

void AHttpService::RegisterResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, class AEntrancePC* PC)
{
	UE_LOG(LogTemp, Warning, TEXT("RegisterResponse"));
	if (!ResponseIsValid(Response, bWasSuccessful))
	{		
		UE_LOG(LogTemp, Warning, TEXT("RegisterResponse - ResponseIsNotValid"));
		return;
	}

	//FResponse_Register RegisterResponse;
	//GetStructFromJsonString<FResponse_Register>(Response, RegisterResponse);

	UE_LOG(LogTemp, Warning, TEXT("Log is : %s"), *(Response->GetContentAsString()));
	
	if (IsSuccess(Response))
	{
		FAccountInfo AccountInfo;
		GetStructFromJsonString<FAccountInfo>(Response, AccountInfo);

		PC->RegistSuccess(AccountInfo);
	}
}

void AHttpService::Login(FRequest_Login LoginInfo, AEntrancePC* PC)
{
	FString ContentJsonString;
	GetJsonStringFromStruct<FRequest_Login>(LoginInfo, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("/login", ContentJsonString);
	Send(Request);
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::LoginResponse, PC);
}

void AHttpService::LoginResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, AEntrancePC* PC)
{
	UE_LOG(LogTemp, Warning, TEXT("LoginResponse"));
	if (!ResponseIsValid(Response, bWasSuccessful))
	{
		UE_LOG(LogTemp, Warning, TEXT("LoginResponse - ResponseIsNotValid"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Log is : %s"), *(Response->GetContentAsString()));

	/*TArray<FAvatarInfo> LoginResponses;

	GetStructFromJsonStringArray<FAvatarInfo>(Response, LoginResponses);*/
	if (IsSuccess(Response))
	{
		FAccountInfo AccountInfo;
		GetStructFromJsonString<FAccountInfo>(Response, AccountInfo);

		PC->LoginSuccess(AccountInfo);
	}
}

void AHttpService::AllAvatarInfo(int32 Idx, AEntrancePC * PC)
{
	FString ContentJsonString;

	FRequest_AccountIdx RequestAccountIdx;
	RequestAccountIdx.Idx = Idx;
	GetJsonStringFromStruct<FRequest_AccountIdx>(RequestAccountIdx, ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("/allAvatarInfo", ContentJsonString);
	Send(Request);
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::AllAvatarInfoResponse, PC);
}

void AHttpService::AllAvatarInfoResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, AEntrancePC * PC)
{
	UE_LOG(LogTemp, Warning, TEXT("AllAvatarInfoResponse"));
	if (!ResponseIsValid(Response, bWasSuccessful))
	{
		UE_LOG(LogTemp, Warning, TEXT("AllAvatarInfoResponse - ResponseIsNotValid"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Log is : %s"), *(Response->GetContentAsString()));
	if (IsSuccess(Response))
	{
		TArray<FAvatarInfo> AvatarInfos;
		
		GetStructFromJsonStringArray<FAvatarInfo>(Response, AvatarInfos);

		PC->AllAvatarInfoSuccess(AvatarInfos);
	}
}

// Called when the game starts or when spawned
void AHttpService::BeginPlay()
{
	Super::BeginPlay();
	Http = &FHttpModule::Get();
	
	/*FRequest_Register RegisterInfo;
	RegisterInfo.accountid = TEXT("UE4Account");
	RegisterInfo.accountname = TEXT("UENickname");
	RegisterInfo.password = TEXT("1234");
	Register(RegisterInfo);*/
}

// Called every frame
void AHttpService::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHttpService::SetAuthorizationHash(FString Hash, TSharedRef<IHttpRequest>& Request)
{
	Request->SetHeader(AuthorizationHeader, Hash);
}

TSharedRef<IHttpRequest> AHttpService::RequestWithRoute(FString Subroute)
{
	TSharedRef<IHttpRequest>Request = Http->CreateRequest();
	FString path = ApiBaseURl + Subroute;
	Request->SetURL(path);
	UE_LOG(LogClass, Warning, TEXT("Path : %s"), *path);
	SetRequestHeaders(Request);
	return Request;
}

void AHttpService::SetRequestHeaders(TSharedRef<IHttpRequest>& Request)
{
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));
}

TSharedRef<IHttpRequest> AHttpService::GetRequest(FString Subroute)
{
	TSharedRef<IHttpRequest> Request = RequestWithRoute(Subroute);
	Request->SetVerb("GET");
	return Request;
}

TSharedRef<IHttpRequest> AHttpService::PostRequest(FString Subroute, FString ContentJsonString)
{
	TSharedRef<IHttpRequest> Request = RequestWithRoute(Subroute);
	Request->SetVerb("POST");
	UE_LOG(LogTemp, Warning, TEXT("ContentJsonString %s"), *ContentJsonString);
	Request->SetContentAsString(ContentJsonString);
	return Request;
}

void AHttpService::Send(TSharedRef<IHttpRequest>& Request)
{
	Request->ProcessRequest();
}

bool AHttpService::ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful || !Response.IsValid())
	{
		return false;
	}

	if (EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Http Response returned error code: %d"), Response->GetResponseCode());
		return false;
	}
}
