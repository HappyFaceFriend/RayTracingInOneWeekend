#include "Sphere.h"

Sphere::Sphere(glm::vec3 position, float radius, std::shared_ptr<Material> material)
    : m_Position(position), m_Radius(radius), m_Material(material)
{}

bool Sphere::Hit(const Ray& ray, Range rayTRange, RayHitInfo& hitInfo) const
{
    auto oc = ray.GetOrigin() - m_Position;
    auto a = glm::dot(ray.GetDirection(), ray.GetDirection());
    auto b = 2.0f * glm::dot(oc, ray.GetDirection());
    auto c = glm::dot(oc, oc) - m_Radius * m_Radius;
    auto D = b * b - 4 * a * c;

    if (D < 0)
        return false;
    float t = (-b - sqrt(D)) / (2.0f * a);
    if (!rayTRange.Surrounds(t))
    {
        t = (-b + sqrt(D)) / (2.0f * a);
        if (!rayTRange.Surrounds(t))
            return false;
    }

    hitInfo.Position = ray.At(t);
    hitInfo.t = t;
    hitInfo.Material = m_Material;

    auto faceNormal = (hitInfo.Position - m_Position) / m_Radius;
    hitInfo.SetFaceNormal(ray, faceNormal);
    return true;

}