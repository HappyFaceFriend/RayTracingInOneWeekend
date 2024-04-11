#include "Lambertian.h"

Lambertian::Lambertian(const glm::vec3& albedo) : m_Albedo(albedo)
{
}

bool Lambertian::Scatter(const Ray& rayIn, const RayHitInfo& hitInfo, glm::vec3& attenuation, Ray& scatteredRay) const
{
	// Always scatter randomly
	auto scatterDirection = hitInfo.Normal + RandomUnitVector();
	if (scatterDirection.length() < FLT_EPSILON)
		scatterDirection = hitInfo.Normal;
	scatteredRay = Ray(hitInfo.Position, glm::normalize(scatterDirection));
	attenuation = m_Albedo;
	return true;
}