#include <iostream>
#include <fstream>

#include <glm/glm.hpp>

#include "Utils.h"
#include "Timer.h"
#include "Camera.h"

#include "Material/Lambertian.h"
#include "Material/Metal.h"
#include "Material/Dielectric.h"

#include "HittableObject/Sphere.h"
#include "HittableObject/HittableList.h"

int main()
{
    Camera camera(400, 255);

    camera.SetVerticalFieldOfView(20);
    camera.SetPosition(glm::vec3(-2, 2, 1));
    camera.SetDirection(glm::vec3(0, 0, -1));

    camera.SetDefocusAngle(10.0f);
    camera.SetFocusDistance(3.7f);

    camera.Initialize();

    //Scene
    HittableList scene;

    auto groundMaterial = std::make_shared<Lambertian>(glm::vec3(0.8, 0.8, 0));
    auto blueMaterial = std::make_shared<Lambertian>(glm::vec3(0.2, 0.2, 0.8));
    auto dielectricGlass = std::make_shared<Dielectric>(1.3);
    auto dielectricGlass2 = std::make_shared<Dielectric>(1.3);
    auto fuzzyMetalMaterial = std::make_shared<Metal>(glm::vec3(0.8, 0.8, 0.8), 0.5);
    auto yellowMaterial = std::make_shared<Lambertian>(glm::vec3(0.8, 0.6, 0.2));

    scene.Add(std::make_shared<Sphere>(glm::vec3(0, -100.5, -1.5), 100.0f, groundMaterial));
    scene.Add(std::make_shared<Sphere>(glm::vec3(-0.6, 0, -2.3), 0.5f, dielectricGlass));
    scene.Add(std::make_shared<Sphere>(glm::vec3(0, 0, -1.5), 0.5f, blueMaterial));
    scene.Add(std::make_shared<Sphere>(glm::vec3(-1.1, 0, -1.5), 0.5f, dielectricGlass2));
    scene.Add(std::make_shared<Sphere>(glm::vec3(-1.1, 0, -1.5), -0.4f, dielectricGlass2));
    scene.Add(std::make_shared<Sphere>(glm::vec3(1.1, 0, -1.5), 0.5f, fuzzyMetalMaterial));
    scene.Add(std::make_shared<Sphere>(glm::vec3(-0.5, -0.33, -0.7), 0.2f, yellowMaterial));

    {
        Timer timer("Render time 1");

        camera.Render(scene, "test.png");
    }

    {
        Timer timer("Render time 2");
        camera.SetSamplesPerPixel(50);
        camera.SetMaxRayBounceCount(50);
        camera.SetDefocusAngle(40);
        camera.SetFocusDistance(4.0f);

        camera.Render(scene, "test2.png");
    }

    
    return 0;
}