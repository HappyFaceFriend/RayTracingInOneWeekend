#pragma once

#include <memory>

#include "Ray.h"
#include "Range.h"

class Material;

struct RayHitInfo
{
	glm::vec3 Position;
	glm::vec3 Normal;
	float t;
	bool IsFrontFace;
	std::shared_ptr<Material> Material;

	void SetFaceNormal(const Ray& ray, const glm::vec3& outwardNormal)
	{
		IsFrontFace = glm::dot(ray.GetDirection(), outwardNormal) < 0;
		Normal = IsFrontFace ? outwardNormal : -outwardNormal;
	}
};

class HittableObject
{
public:
	virtual ~HittableObject() = default;

	virtual bool Hit(const Ray& ray, Range rayTRange, RayHitInfo& hitInfo) const = 0;
};