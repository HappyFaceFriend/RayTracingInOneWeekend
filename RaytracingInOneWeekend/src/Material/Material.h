#pragma once

#include <glm/glm.hpp>

#include "Range.h"
#include "Ray.h"
#include "HittableObject/HittableObject.h"
#include "Utils.h"

class Material
{
public:
	virtual ~Material() = default;

	virtual bool Scatter(const Ray& rayIn, const RayHitInfo& hitInfo, glm::vec3& attenuation, Ray& scatteredRay) const = 0;
};