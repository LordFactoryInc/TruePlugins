// (c) Lord Factory Inc.

#pragma once

#include "CoreMinimal.h"

/**
 * TruePhysics
 */

namespace TruePhysics
{
	constexpr float cAirDensity = 1.2 / (100 * 100 * 100); //kg/cm^3

	FORCEINLINE float GetAirResistanceCoeff(float Cx, float S)
	{
		return 0.5f * Cx * S * cAirDensity;
	}
}