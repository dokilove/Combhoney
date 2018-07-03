// Fill out your copyright notice in the Description page of Project Settings.

#include "HttpService.h"


// Sets default values
AHttpService::AHttpService()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AHttpService::Register(FRequest_Register RegisterInfo)
{
	FString ContentJsonString;
	GetJsonStringFromStruct<FRequest_Register>(RegisterInfo, ContentJsonString);
	UE_LOG(LogTemp, Warning, TEXT("ContentJsonString %s"), *ContentJsonString);
	TSharedRef<IHttpRequest> Request = PostRequest("/register", ContentJsonString);
	//TSharedRef<IHttpRequest> Request = GetRequest("/login");
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::RegisterResponse);
	Send(Request);
}

void AHttpService::RegisterResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("RegisterResponse"));
	if (!ResponseIsValid(Response, bWasSuccessful))
	{		
		UE_LOG(LogTemp, Warning, TEXT("RegisterResponse - ResponseIsNotValid"));
		return;
	}

	FResponse_Register RegisterResponse;
	GetStructFromJsonString<FResponse_Register>(Response, RegisterResponse);

	UE_LOG(LogTemp, Warning, TEXT("Log is : %s"), *(Response->GetContentAsString()));
}

// Called when the game starts or when spawned
void AHttpService::BeginPlay()
{
	Super::BeginPlay();
	Http = &FHttpModule::Get();
	
	FRequest_Register RegisterInfo;
	RegisterInfo.id = TEXT("UnrealUser");
	RegisterInfo.nickname = TEXT("UENickname");
	RegisterInfo.password = TEXT("123456");
	Register(RegisterInfo);
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