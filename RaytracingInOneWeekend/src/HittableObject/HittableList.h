#pragma once

#include <memory>
#include <vector>

#include "HittableObject.h"

class HittableList : public HittableObject
{
public:
	HittableList() = default;
	
	bool Hit(const Ray& ray, Range rayTRange, RayHitInfo& hitInfo) const override;

	void Add(std::shared_ptr<HittableObject> object) { m_Objects.push_back(object); }
	void Clear() { m_Objects.clear(); }

	const std::vector<std::shared_ptr<HittableObject>>& GetObjects() const { return m_Objects; }

private:
	std::vector<std::shared_ptr<HittableObject>> m_Objects;
};