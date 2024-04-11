#pragma once

#include "Utils.h"

struct Range
{
public:
	float Min, Max;

	Range() : Min(INFINITY_FLOAT), Max(-INFINITY_FLOAT) {}
	Range(float min, float max) : Min(min), Max(max) {}

	bool Contains(float f) const { return Min <= f && f <= Max; }
	bool Surrounds(float f) const { return Min < f && f < Max; }
	float Clamp(float f) const
	{
		if (f < Min) return Min;
		if (f > Max) return Max;
		return f;
	}

	static const Range Empty;
	static const Range Universe;
};
