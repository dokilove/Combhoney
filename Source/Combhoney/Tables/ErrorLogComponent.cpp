// Fill out your copyright notice in the Description page of Project Settings.

#include "ErrorLogComponent.h"
#include "ConstructorHelpers.h"


// Sets default values for this component's properties
UErrorLogComponent::UErrorLogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...



	if (ErrorLogTable == nullptr)
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> DT_ErrorLogTable(TEXT("DataTable'/Game/Blueprints/Tables/ErrorLog.ErrorLog'"));
		if (DT_ErrorLogTable.Succeeded())
		{
			ErrorLogTable = DT_ErrorLogTable.Object;
		}
		UE_LOG(LogClass, Warning, TEXT("ErrorLogTable Create!"));
	}
}


// Called when the game starts
void UErrorLogComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UErrorLogComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FErrorLogTable & UErrorLogComponent::GetErrorLogData(int ErrorCode)
{
	// TODO: insert return statement here
	return *ErrorLogTable->FindRow<FErrorLogTable>(*FString::FromInt(ErrorCode), TEXT("ErrorCode"), true);
}