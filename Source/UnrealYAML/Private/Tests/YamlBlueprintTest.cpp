#include "Misc/AutomationTest.h"
#include "YamlBlueprintExample.h"

#if WITH_DEV_AUTOMATION_TESTS

#if ENGINE_MAJOR_VERSION >= 5
IMPLEMENT_SIMPLE_AUTOMATION_TEST(YamlBlueprinttest, "UnrealYAML.Blueprint",
                                 EAutomationTestFlags_ApplicationContextMask | EAutomationTestFlags::ProductFilter)
#else
IMPLEMENT_SIMPLE_AUTOMATION_TEST(YamlBlueprinttest, "UnrealYAML.Blueprint",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
#endif

bool YamlBlueprinttest::RunTest(const FString& Parameters)
{
#if ENGINE_MAJOR_VERSION < 5
    AddWarning(TEXT("Skipping UnrealYAML.Blueprint: test requires UE5 or newer."));
    return true;
#endif

    const TCHAR* BlueprintClassPath = TEXT("/UnrealYAML/Blueprints/BP_YamlExample.BP_YamlExample_C");
    UClass* BlueprintClass = LoadClass<UYamlBlueprintExample>(nullptr, BlueprintClassPath);
    if (!TestNotNull(TEXT("Load BP_YamlExample class"), BlueprintClass)) {
        return false;
    }

    UYamlBlueprintExample* Example = NewObject<UYamlBlueprintExample>(GetTransientPackage(), BlueprintClass);
    if (!TestNotNull(TEXT("Instantiate BP_YamlExample"), Example)) {
        return false;
    }

    {
        const FString ValidYaml = TEXT(R"yaml(
name: Rogue
health: 100
speed: 7.5
abilities:
  - Dash
  - Cloak
)yaml");

        FYamlParseIntoResult ValidResult;
        FYamlBlueprintExampleStruct ValidStruct;
        const bool bValidParse = Example->DemoYamlParse(ValidYaml, ValidResult, ValidStruct, true);

        TestTrue(TEXT("Valid YAML parse bool return"), bValidParse);
        TestTrue(TEXT("Valid YAML parse success"), ValidResult.Success());
        TestEqual(TEXT("Valid YAML parse has no errors"), ValidResult.Errors.Num(), 0);
        TestEqual(TEXT("Valid YAML Name"), ValidStruct.Name, FString(TEXT("Rogue")));
        TestEqual(TEXT("Valid YAML Health"), ValidStruct.Health, 100);
        TestEqual(TEXT("Valid YAML Speed"), ValidStruct.Speed, 7.5f);
        if (TestEqual(TEXT("Valid YAML Abilities count"), ValidStruct.Abilities.Num(), 2)) {
            TestEqual(TEXT("Valid YAML Abilities[0]"), ValidStruct.Abilities[0], FString(TEXT("Dash")));
            TestEqual(TEXT("Valid YAML Abilities[1]"), ValidStruct.Abilities[1], FString(TEXT("Cloak")));
        }
    }

    const FString InvalidYaml = TEXT("name: [not a scalar]");
    
    {
        FYamlParseIntoResult InvalidResult;
        FYamlBlueprintExampleStruct InvalidStruct;
        const bool bInvalidParse = Example->DemoYamlParse(InvalidYaml, InvalidResult, InvalidStruct, true);

        TestFalse(TEXT("Invalid YAML parse bool return"), bInvalidParse);
        TestFalse(TEXT("Invalid YAML parse fails"), InvalidResult.Success());
        if (TestEqual(TEXT("Invalid YAML parse has errors"), InvalidResult.Errors.Num(), 1)) {
            TestEqual(
                TEXT("Invalid YAML parse has expected error"),
                InvalidResult.Errors[0],
                FString(TEXT(".Name: value is not a scalar"))
            );
        }
    }

    {
        FYamlParseIntoResult LaxInvalidResult;
        FYamlBlueprintExampleStruct LaxInvalidStruct;
        const bool bLaxInvalidParse = Example->DemoYamlParse(InvalidYaml, LaxInvalidResult, LaxInvalidStruct, false);

        TestTrue(TEXT("Invalid YAML parse bool return when strict=false"), bLaxInvalidParse);
        TestTrue(TEXT("Invalid YAML parse success when strict=false"), LaxInvalidResult.Success());
        TestEqual(TEXT("Invalid YAML parse has no errors when strict=false"), LaxInvalidResult.Errors.Num(), 0);
    }

    return !HasAnyErrors();
}

#endif
