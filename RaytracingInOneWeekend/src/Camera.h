#pragma once

#include <glm/glm.hpp>
#include <lodepng.h>

#include "HittableObject/HittableList.h"
#include "Material/Material.h"

class Camera
{
public:

	Camera(int imageWidth, int imageHeight);

	void Initialize();

	void Render(const HittableObject& hittable, const std::string& imagePath);

	void SetImageSize(int width, int height);

#pragma region Getters/Setters

	int GetImageWidth() const { return m_ImageWidth; }
	int GetImageHeight() const { return m_ImageHeight; }

	void SetSamplesPerPixel(int samplesPerPixel) { m_SamplesPerPixel = samplesPerPixel; }
	int GetSamplesPerPixel() const { return m_SamplesPerPixel; }

	void SetMaxRayBounceCount(int maxRayBounceCount) { m_MaxRayBounceCount = maxRayBounceCount; }
	int GetMaxRayBounceCount() const { return m_MaxRayBounceCount; }

	void SetVerticalFieldOfView(float vFov) { m_VFov = vFov; }
	float GetSetVerticalFieldOfView() const { return m_VFov; }

	void SetPosition(const glm::vec3& position) { m_Position = position; }
	glm::vec3 GetPosition() const { return m_Position; }

	void SetDirection(const glm::vec3& direction) { m_Direction = direction; }
	glm::vec3 GetDirection() const { return m_Direction; }

	void SetDefocusAngle(float defocusAngle) { m_DefocusAngle = defocusAngle; }
	float GetDefocusAngle() const { return m_DefocusAngle; }

	void SetFocusDistance(float focusDistance) { m_FocusDistance = focusDistance; }
	float GetFocusDistance() const { return m_FocusDistance; }

#pragma endregion

private:
	void SaveAsPng(const std::vector<unsigned char>& pixels, const std::string& imagePath);
	glm::vec3 SampleDefocusDisk() const;

	Ray GetRandomRay(int u, int v) const;
	glm::vec3 RandomSquare() const;
	glm::vec3 GetRayColor(const Ray& ray, const HittableObject& hittable, int bouncedCount) const;

private:
	static constexpr float RAY_T_MIN_VALUE = 0.001f;

	int m_SamplesPerPixel = 10;
	int m_MaxRayBounceCount = 10;
	int m_ImageWidth;
	int m_ImageHeight;

	float m_VFov = 90;
	glm::vec3 m_Position{};
	glm::vec3 m_Direction{};
	glm::vec3 m_ViewUp{0.0f, 1.0f, 0.0f};

	float m_DefocusAngle = 0;
	float m_FocusDistance = 10;

	//Calculated at Initialize()
	glm::vec3 m_Pixel00{};
	glm::vec3 m_PixelDeltaU{};
	glm::vec3 m_PixelDeltaV{};
	glm::vec3 m_DefocusDiskU{};
	glm::vec3 m_DefocusDiskV{};
};