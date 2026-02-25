#pragma once

#include "CoreMinimal.h"
#include "YamlParsing.h"
#include "UObject/Object.h"
#include "YamlBlueprintExample.generated.h"

/**
 * Demonstrates how blueprints can parse YAML in to a USTRUCT.
 */
USTRUCT(BlueprintType)
struct FYamlBlueprintExampleStruct
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name;

    UPROPERTY(BlueprintReadOnly)
    int32 Health;

    UPROPERTY(BlueprintReadOnly)
    float Speed;

    UPROPERTY(BlueprintReadOnly)
    TArray<FString> Abilities; 
};

/**
 * Glue to expose a BP implementation to CPP tests. Only used for UnrealYAML tests.
 */
UCLASS(Blueprintable, Abstract, MinimalAPI)
class UYamlBlueprintExample : public UObject
{
    GENERATED_BODY()

public:
    /**
     * Implemented by Content/Blueprints/BP_YamlExample.uasset. Can be called from CPP. 
     */
    UFUNCTION(BlueprintImplementableEvent)
    bool DemoYamlParse(
        const FString& Yaml,
        FYamlParseIntoResult& OutResult,
        FYamlBlueprintExampleStruct& OutStruct,
        const bool Strict = false
    );
};
