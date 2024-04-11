#include "Utils.h"

#include <random>

glm::vec3 LinearToGamma(const glm::vec3& linearColor) 
{ 
    return glm::sqrt(linearColor);
}

glm::vec3 operator*(const glm::vec3& vec, int i)
{
    return glm::vec3(vec.x * i, vec.y * i, vec.z * i);
}
glm::vec3 operator*(int i, const glm::vec3& vec)
{
    return glm::vec3(vec.x * i, vec.y * i, vec.z * i);
}
glm::vec3 operator/(const glm::vec3& vec, int i)
{
    return glm::vec3(vec.x / i, vec.y / i, vec.z / i);
}

glm::vec3 Reflect(const glm::vec3& v, const glm::vec3& n)
{
    return v - 2 * glm::dot(v, n) * n;
}

glm::vec3 Refract(const glm::vec3& v, const glm::vec3& n, double eta) 
{
    auto cosTheta = fmin(glm::dot(-v, n), 1.0);
    glm::vec3 perpR = eta * (v + cosTheta * n);
    glm::vec3 parallelR = -sqrt(fabs(1.0 - glm::dot(perpR, perpR))) * n;
    return perpR + parallelR;
}

float RandomValue()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
float RandomRange(float min, float max)
{
    return min + (max - min) * RandomValue();
}
glm::vec3 RandomVectorInUnitDisk()
{
    float theta = RandomRange(0, 2 * PI);
    return RandomValue() * glm::vec3(cos(theta), sin(theta), 0.0f);
}
glm::vec3 RandomUnitVector()
{
    return glm::normalize(glm::vec3(RandomRange(-1, 1), RandomRange(-1, 1), RandomRange(-1, 1)));
}
glm::vec3 RandomUnitVectorOnHemisphere(const glm::vec3 normal)
{
    glm::vec3 unitVector = RandomUnitVector();
    if (glm::dot(unitVector, normal) > 0.0)
        return unitVector;
    else
        return -unitVector;
}
