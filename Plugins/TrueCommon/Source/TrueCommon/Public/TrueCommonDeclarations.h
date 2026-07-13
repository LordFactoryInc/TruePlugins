// (c) Lord Factory Inc.

#pragma once

/**
 * Common C++ utility functions
 */

#include "CoreMinimal.h"
#include "EngineUtils.h"

#include "TrueCommonDeclarations.generated.h"

DECLARE_DYNAMIC_DELEGATE(FDynamicDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDynamicMulticastDelegate);

/**
 * Dummy UCLASS for correct code generation for DECLARE_DELEGATE macros
 */
UCLASS()
class UTrueCommonDelegates : public UObject
{
	GENERATED_BODY()
};
