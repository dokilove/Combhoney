// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ErrorLogTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct COMBHONEY_API FErrorLogTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Table")
		int ErrorCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Table")
		FString Desc;
	
	
};
