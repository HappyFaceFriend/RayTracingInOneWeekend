#pragma once

#include <limits>

#include <glm/glm.hpp>

constexpr float INFINITY_FLOAT = std::numeric_limits<float>::infinity();
constexpr float PI = 3.1415926535897932385f;


glm::vec3 operator*(const glm::vec3& vec, int i);
glm::vec3 operator*(int i, const glm::vec3& vec);
glm::vec3 operator/(const glm::vec3& vec, int i);

glm::vec3 Reflect(const glm::vec3& v, const glm::vec3& n);
glm::vec3 Refract(const glm::vec3& v, const glm::vec3& n, double eta);

glm::vec3 LinearToGamma(const glm::vec3& linearColor);

float RandomValue();
float RandomRange(float min, float max);
glm::vec3 RandomVectorInUnitDisk();
glm::vec3 RandomUnitVector();
glm::vec3 RandomUnitVectorOnHemisphere(const glm::vec3 normal);
