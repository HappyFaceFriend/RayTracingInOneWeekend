#pragma once

#include "Material.h"

class Metal : public Material
{
public:
	Metal(const glm::vec3& albedo, float fuzziness);

	bool Scatter(const Ray& rayIn, const RayHitInfo& hitInfo, glm::vec3& attenuation, Ray& scatteredRay) const override;

private:
	glm::vec3 m_Albedo;
	float m_Fuzziness;
};