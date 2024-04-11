#include "HittableList.h"

#include "Range.h"

bool HittableList::Hit(const Ray& ray, Range rayTRange, RayHitInfo& hitInfo) const
{
    RayHitInfo tempHitInfo;
    bool hit = false;
    float shortestDistance = rayTRange.Max;

    for (const auto& object : m_Objects)
    {
        if (object->Hit(ray, Range(rayTRange.Min, shortestDistance), tempHitInfo))
        {
            hit = true;
            shortestDistance = tempHitInfo.t;
        }
    }
    if (hit)
        hitInfo = tempHitInfo;
    else
        hitInfo = RayHitInfo();

    return hit;
}