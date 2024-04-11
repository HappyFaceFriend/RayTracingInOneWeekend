#pragma once

#include "Material.h"

class Lambertian : public Material
{
public:
	Lambertian(const glm::vec3& albedo);

	bool Scatter(const Ray& rayIn, const RayHitInfo& hitInfo, glm::vec3& attenuation, Ray& scatteredRay) const override;

private:
	glm::vec3 m_Albedo;
};