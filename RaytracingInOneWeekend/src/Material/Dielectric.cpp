#include "Dielectric.h"

static float GetReflectance(float cosine, float refractiveIndex)
{
	// Schlick's approximation
	float r0 = (1 - refractiveIndex) / (1 + refractiveIndex);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

Dielectric::Dielectric(float refractiveIndex) : m_RefractiveIndex(refractiveIndex)
{
}

bool Dielectric::Scatter(const Ray& rayIn, const RayHitInfo& hitInfo, glm::vec3& attenuation, Ray& scatteredRay) const
{
	// Snell's law
	attenuation = glm::vec3(1, 1, 1);
	float eta = hitInfo.IsFrontFace ? 1 / m_RefractiveIndex : m_RefractiveIndex;

	glm::vec3 normalizedDirection = glm::normalize(rayIn.GetDirection());

	float cosTheta = fmin(glm::dot(-normalizedDirection, hitInfo.Normal), 1);
	float sinTheta = sqrt(1 - cosTheta * cosTheta);

	bool cannotRefract = eta * sinTheta > 1.0f;
	glm::vec3 direction;
	if (cannotRefract || GetReflectance(cosTheta, eta) > RandomValue())
		direction = Reflect(normalizedDirection, hitInfo.Normal);
	else
		direction = Refract(normalizedDirection, hitInfo.Normal, eta);

	scatteredRay = Ray(hitInfo.Position, direction);
	return true;
}
