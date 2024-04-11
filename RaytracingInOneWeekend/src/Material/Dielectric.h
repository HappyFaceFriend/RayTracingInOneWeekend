#pragma once

#include "Material.h"

class Dielectric : public Material
{
public:
	Dielectric(float refractiveIndex);

	bool Scatter(const Ray& rayIn, const RayHitInfo& hitInfo, glm::vec3& attenuation, Ray& scatteredRay) const override;

private:
	float m_RefractiveIndex;
};
