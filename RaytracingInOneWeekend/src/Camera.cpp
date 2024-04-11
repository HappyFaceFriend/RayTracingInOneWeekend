#include "Camera.h"

#include <iostream>

Camera::Camera(int imageWidth, int imageHeight)
	:m_ImageWidth(imageWidth), m_ImageHeight(imageHeight)
{
}

void Camera::Initialize()
{
	float theta = glm::radians(m_VFov);
	float viewportHeight = 2 * tan(theta / 2) * m_FocusDistance;
	float viewportWidth = viewportHeight * (static_cast<float>(m_ImageWidth) / m_ImageHeight);

	auto w = glm::normalize(m_Position - m_Direction);
	auto u = glm::normalize(cross(m_ViewUp, w));
	auto v = glm::cross(w, u);

	auto viewportU = viewportWidth * u;
	auto viewportV = viewportHeight * -v;
	m_PixelDeltaU = viewportU / m_ImageWidth;
	m_PixelDeltaV = viewportV / m_ImageHeight;

	auto viewportUpperLeft = m_Position - m_FocusDistance * w - viewportU / 2.0f - viewportV / 2.0f;
	m_Pixel00 = viewportUpperLeft + 0.5f * (m_PixelDeltaU + m_PixelDeltaV);

	auto defocusRadius = m_FocusDistance * tan(glm::radians(m_DefocusAngle / 2));
	m_DefocusDiskU = u * defocusRadius;
	m_DefocusDiskV = v * defocusRadius;

}

void Camera::Render(const HittableObject& hittable, const std::string& imagePath)
{
	std::vector<unsigned char> pixels(m_ImageHeight * m_ImageWidth * 4);

	for (int j = 0; j < m_ImageHeight; ++j)
	{
		std::clog << "\rScanlines remaining: " << (m_ImageHeight - j) << "/" << m_ImageHeight << std::flush;
		for (int i = 0; i < m_ImageWidth; ++i)
		{
			glm::vec3 pixelColor(0.0f, 0.0f, 0.0f);
			for (int sample = 0; sample < m_SamplesPerPixel; sample++)
			{
				Ray ray = GetRandomRay(i, j);
				pixelColor += GetRayColor(ray, hittable, 0) * 1.0f / m_SamplesPerPixel;
			}

			auto finalColor = LinearToGamma(pixelColor);
			int ir = static_cast<unsigned char>(255.999 * finalColor.r);
			int ig = static_cast<unsigned char>(255.999 * finalColor.g);
			int ib = static_cast<unsigned char>(255.999 * finalColor.b);

			pixels[4 * (m_ImageWidth * j + i) + 0] = ir;
			pixels[4 * (m_ImageWidth * j + i) + 1] = ig;
			pixels[4 * (m_ImageWidth * j + i) + 2] = ib;
			pixels[4 * (m_ImageWidth * j + i) + 3] = 255;
		}
	}
	std::clog << "Done.\n";

	SaveAsPng(pixels, imagePath);
}

void Camera::SetImageSize(int width, int height)
{
	m_ImageWidth = width;
	m_ImageHeight = height;
}

void Camera::SaveAsPng(const std::vector<unsigned char>& pixels, const std::string& imagePath)
{

	//Save as PNG
	std::vector<unsigned char> pngData;

	auto error = lodepng::encode(pngData, pixels, m_ImageWidth, m_ImageHeight);
	if (!error)
		lodepng::save_file(pngData, imagePath);

	//if there's an error, display it
	if (error)
		std::clog << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
	else
		std::clog << "Saved image file at " << imagePath << std::endl;

}

glm::vec3 Camera::SampleDefocusDisk() const
{
	auto p = RandomVectorInUnitDisk();
	return m_Position + p.x * m_DefocusDiskU + p.y * m_DefocusDiskV;
}

Ray Camera::GetRandomRay(int u, int v) const
{
	auto pixelCenter = m_Pixel00 + (u * m_PixelDeltaU) + (v * m_PixelDeltaV);
	auto pixelSaample = pixelCenter + RandomSquare();

	auto rayOrigin = m_DefocusAngle <= 0 ? m_Position : SampleDefocusDisk();

	return Ray(rayOrigin, pixelSaample - rayOrigin);
}

glm::vec3 Camera::RandomSquare() const
{
	// Returns a random point in the square surrounding a pixel at the origin.
	auto px = -0.5f + RandomValue();
	auto py = -0.5f + RandomValue();
	return (px * m_PixelDeltaU) + (py * m_PixelDeltaV);
}

glm::vec3 Camera::GetRayColor(const Ray& ray, const HittableObject& hittable, int bouncedCount) const
{
	if (bouncedCount >= m_MaxRayBounceCount)
		return glm::vec3(0, 0, 0);

	RayHitInfo hitInfo;
	if (hittable.Hit(ray, Range(RAY_T_MIN_VALUE, INFINITY_FLOAT), hitInfo))
	{
		Ray scatteredRay;
		glm::vec3 attenuation;
		if (hitInfo.Material->Scatter(ray, hitInfo, attenuation, scatteredRay))
			return attenuation * GetRayColor(scatteredRay, hittable, bouncedCount + 1);
		return glm::vec3(0, 0, 0);
	}

	glm::vec3 unitDirection = ray.GetDirection();
	auto factor = 0.5f * (unitDirection.y + 1.0f);

	return factor * glm::vec3(0.5f, 0.7f, 1.0f) + (1.0f - factor) * glm::vec3(1.0f, 1.0f, 1.0f);
}