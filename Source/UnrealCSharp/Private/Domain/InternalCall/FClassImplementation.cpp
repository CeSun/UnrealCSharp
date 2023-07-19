﻿#include "Domain/InternalCall/FClassImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/Property/TPropertyBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/BindingMacro.h"
#include "Macro/NamespaceMacro.h"

BINDING_REFLECTION_CLASS(UClass);

struct FRegisterUClass
{
	FRegisterUClass()
	{
		TReflectionClassBuilder<UClass>(NAMESPACE_LIBRARY)
			.Property("ClassDefaultObject", BINDING_READONLY_PROPERTY(&UClass::ClassDefaultObject))
			.Function("GetDefaultObject",
			          static_cast<void*>(FClassImplementation::Class_GetDefaultObjectImplementation))
			.Register();
	}
};

static FRegisterUClass RegisterUClass;

void FClassImplementation::Class_GetDefaultObjectImplementation(const MonoObject* InMonoObject,
                                                                const bool bCreateIfNeeded, MonoObject** OutValue)
{
	if (const auto FoundClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(InMonoObject))
	{
		const auto Object = FoundClass->GetDefaultObject(bCreateIfNeeded);

		*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Object);
	}
}
