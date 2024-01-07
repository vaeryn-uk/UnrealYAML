﻿#pragma once

#include "TestStructs.generated.h"


// SimpleYaml
USTRUCT()
struct FSimpleStruct {
    GENERATED_BODY()

    UPROPERTY()
    FString Str;

    UPROPERTY()
    int32 Int{};

    UPROPERTY()
    bool Bool{};

    UPROPERTY()
    TArray<int32> Arr;

    UPROPERTY()
    TMap<FString, int32> Map;
};

// SimpleYaml
USTRUCT()
struct FDefaultedStruct {
    GENERATED_BODY()

    UPROPERTY()
    FString Str = TEXT("a string");

    UPROPERTY()
    int32 Int = 1;

    UPROPERTY()
    bool Bool = true;

    UPROPERTY()
    TArray<int32> Arr = {1, 2, 3};

    UPROPERTY()
    TMap<FString, int32> Map = {{"foo", 13}};
};

UENUM()
enum class EAnEnum {
    Value1 = 0,
    Value2 = 1,
    Value3 = 2,
};

USTRUCT()
struct FChildStruct {
    GENERATED_BODY()

    UPROPERTY()
    TArray<FString> SomeValues;

    UPROPERTY()
    float AFloat;

    UPROPERTY()
    TEnumAsByte<EAnEnum> AnEnum = EAnEnum::Value3;
};

USTRUCT()
struct FParentStruct {
    GENERATED_BODY()

    UPROPERTY()
    FChildStruct Embedded;

    UPROPERTY()
    TArray<FChildStruct> Children;

    UPROPERTY()
    TMap<TEnumAsByte<EAnEnum>, FChildStruct> MappedChildren;
};

USTRUCT()
struct FEnumAsByteStruct {
    GENERATED_BODY()

    UPROPERTY()
    TEnumAsByte<EAnEnum> AnEnum;
};

USTRUCT()
struct FEnumStruct {
    GENERATED_BODY()

    UPROPERTY()
    EAnEnum AnEnum;
};

// Cannot test for complex yaml, as we can't represent mixed nested types :(
