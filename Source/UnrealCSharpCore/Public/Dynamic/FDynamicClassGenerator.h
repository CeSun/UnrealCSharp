#pragma once

#include "Dynamic/CSharpClass.h"
#include "Dynamic/CSharpBlueprintGeneratedClass.h"
#include "mono/metadata/object.h"

class FDynamicClassGenerator
{
public:
	static void Generator();

#if WITH_EDITOR
	static void CodeAnalysisGenerator();
#endif

	static void Generator(MonoClass* InMonoClass, bool bReInstance = false);

	static bool IsDynamicClass(MonoClass* InMonoClass);

private:
	static void BeginGenerator(UClass* InClass, UClass* InParentClass);

	static void BeginGenerator(UCSharpBlueprintGeneratedClass* InClass, UClass* InParentClass);

	static void EndGenerator(UClass* InClass);

	static UCSharpClass* GeneratorCSharpClass(
		UPackage* InOuter, const FString& InName, UClass* InParentClass);

	static UCSharpBlueprintGeneratedClass* GeneratorCSharpBlueprintGeneratedClass(
		UPackage* InOuter, const FString& InName, UClass* InParentClass);

#if WITH_EDITOR
	static void ReInstance(UClass* InClass);
#endif

	static void GeneratorProperty(MonoClass* InMonoClass, UClass* InClass);

	static void GeneratorFunction(MonoClass* InMonoClass, UClass* InClass);
};
