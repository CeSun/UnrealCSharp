#pragma once

#include "TArgument.inl"
#include "TOut.inl"
#include "TReturnValue.inl"
#include "Environment/FCSharpEnvironment.h"

inline MonoObject* Get(MonoArray* InMonoArray, const SIZE_T InIndex)
{
	return ARRAY_GET(InMonoArray, MonoObject*, InIndex);
}

template <typename>
struct TFunctionHelper
{
};

template <typename Result, typename... Args>
struct TFunctionHelper<TPair<Result, TTuple<Args...>>>
{
	template <typename Function, SIZE_T... Index>
	static void Call(Function InFunction, TIntegerSequence<SIZE_T, Index...>, BINDING_FUNCTION_SIGNATURE)
	{
		TTuple<TArgument<Args>...> Argument(Get(InValue, Index)...);

		if constexpr (TIsSame<Result, void>::Value)
		{
			InFunction(Forward<Args>(Argument.template Get<Index>().Get())...);
		}
		else
		{
			*ReturnValue = TReturnValue<Result>(Forward<Result>(
					InFunction(Forward<Args>(Argument.template Get<Index>().Get())...)))
				.Get();
		}

		TOut(OutValue, Argument).template Get<0, Args...>();
	}

	template <typename Class, typename Function, SIZE_T... Index>
	static void Call(Function InFunction, TIntegerSequence<SIZE_T, Index...>, BINDING_FUNCTION_SIGNATURE)
	{
		if (auto FoundObject = FCSharpEnvironment::TGetObject<Class, Class>()(
			FCSharpEnvironment::GetEnvironment(), InMonoObject))
		{
			TTuple<TArgument<Args>...> Argument(Get(InValue, Index)...);

			if constexpr (TIsSame<Result, void>::Value)
			{
				(FoundObject->*InFunction)(Forward<Args>(Argument.template Get<Index>().Get())...);
			}
			else
			{
				*ReturnValue = TReturnValue<Result>(Forward<Result>(
						(FoundObject->*InFunction)(Forward<Args>(Argument.template Get<Index>().Get())...)))
					.Get();
			}

			TOut(OutValue, Argument).template Get<0, Args...>();
		}
	}
};