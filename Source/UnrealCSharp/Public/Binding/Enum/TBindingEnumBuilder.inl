#pragma once

#include "Binding/FBinding.h"
#include "Binding/Enum/FBindingEnumRegister.h"
#include "Binding/TypeInfo/TTypeInfo.inl"
#include "CoreMacro/BindingMacro.h"

template <typename T, bool bIsEngineEnum = false>
class TBindingEnumBuilder
{
public:
	explicit TBindingEnumBuilder() :
		EnumRegister(FBinding::Get().Register({[]() { return TName<T, T>::Get(); }},
		                                      TName<std::underlying_type_t<T>, std::underlying_type_t<T>>::Get(),
		                                      bIsEngineEnum
#if WITH_TYPE_INFO
		                                      , {[]() { return TTypeInfo<T>::Get(); }}
#endif
			)
		)
	{
	}

public:
	template <typename Type>
	TBindingEnumBuilder& Enumerator(const FString& InKey, const Type InValue)
	{
		EnumRegister->BindingEnumerator(InKey, static_cast<std::underlying_type_t<Type>>(InValue));

		return *this;
	}

private:
	FBindingEnumRegister*& EnumRegister;
};
