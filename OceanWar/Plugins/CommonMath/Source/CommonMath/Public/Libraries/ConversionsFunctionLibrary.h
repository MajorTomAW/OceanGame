// Copyright © 2024 MajorT. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ConversionsFunctionLibrary.generated.h"

struct FCommonMath
{
	template<typename Value>
	static float FindBiggestValue(const TArray<Value>& InArray)
	{
		float OutValue = InArray[0];
		for (int32 i = 1; i < InArray.Num(); i++)
		{
			if (InArray[i] > OutValue)
			{
				OutValue = InArray[i];
			}
		}
		return OutValue;
	}
};

/**
 * 
 */
UCLASS()
class COMMONMATH_API UConversionsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
	
	/** Gravity Constant */
	UFUNCTION(BlueprintPure, Category = "Common Projectile|Gravity", meta = (DisplayName = "Get Gravity Constant in m/s²", CompactNodeTitle = "G in m/s²", Keywords = "gravity constant g m/s²"))
	static float GetGravityConstant() {return 9.81f;}

	UFUNCTION(BlueprintPure, Category = "Common Projectile|Gravity", meta = (DisplayName = "Get Gravity Constant in cm/s²", CompactNodeTitle = "G in cm/s²", Keywords = "gravity constant g cm/s²"))
	static float GetGravityConstantInCmS() {return 981.0f;}

	/** Conversions */
	UFUNCTION(BlueprintPure, Category = "Common Math|Conversions", meta = (DisplayName = "Convert cm/s to km/h", CompactNodeTitle = "cm/s to km/h", Keywords = "convert cm/s km/h"))
	static float ConvertCmSToKmH(float CmS) {return CmS * 0.036f;}

	UFUNCTION(BlueprintPure, Category = "Common Math|Conversions", meta = (DisplayName = "Convert km/h to cm/s", CompactNodeTitle = "km/h to cm/s", Keywords = "convert km/h cm/s"))
	static float ConvertKmHToCmS(float KmH) {return KmH * 27.7778f;}

	UFUNCTION(BlueprintPure, Category = "CommonMath|Array", meta = (DisplayName = "Get Biggest Value (float)", Keywords = "biggest value float"))
	static float GetBiggestValueFloat(const TArray<float>& InArray) {return FCommonMath::FindBiggestValue<float>(InArray); }

	UFUNCTION(BlueprintPure, Category = "CommonMath|Array", meta = (DisplayName = "Get Biggest Value (int)", Keywords = "biggest value int"))
	static int32 GetBiggestValueInt(const TArray<int32>& InArray) {return FCommonMath::FindBiggestValue<int32>(InArray); }
};
