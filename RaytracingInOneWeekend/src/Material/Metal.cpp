#include "Metal.h"

Metal::Metal(const glm::vec3& albedo, float fuzziness) : m_Albedo(albedo), m_Fuzziness(fuzziness)
{
}

bool Metal::Scatter(const Ray& rayIn, const RayHitInfo& hitInfo, glm::vec3& attenuation, Ray& scatteredRay) const
{
	auto reflectedDirection = Reflect(glm::normalize(rayIn.GetDirection()), hitInfo.Normal);
	reflectedDirection += RandomUnitVector() * m_Fuzziness;
	scatteredRay = Ray(hitInfo.Position, reflectedDirection);
	attenuation = m_Albedo;
	return glm::dot(reflectedDirection, hitInfo.Normal) > 0;
}