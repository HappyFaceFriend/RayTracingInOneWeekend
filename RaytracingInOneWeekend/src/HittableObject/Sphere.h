#pragma once

#include <memory>

#include "HittableObject.h"

class Sphere : public HittableObject
{
public:
	Sphere(glm::vec3 position, float radius, std::shared_ptr<Material> material);

	virtual bool Hit(const Ray& ray, Range rayTRange, RayHitInfo& hitInfo) const override;

private:
	glm::vec3 m_Position{ 0, 0, 0 };
	float m_Radius = 1.0f;
    std::shared_ptr<Material> m_Material;
};