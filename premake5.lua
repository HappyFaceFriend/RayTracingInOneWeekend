--premake5.lua

workspace "RayTracingInOneWeekend"
	architecture "x64"
	startproject "RayTracingInOneWeekend"
	configurations {"Debug", "Release"}
	platforms {"Win64"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "RayTracingInOneWeekend"
	location "RayTracingInOneWeekend"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",

		"%{prj.name}/vendor/lodepng/lodepng.h",
		"%{prj.name}/vendor/lodepng/lodepng.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/glm",
		"%{prj.name}/vendor/lodepng"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
