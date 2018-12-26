workspace "FractalViewer"
	architecture "x86_64"
	configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "FractalViewer"
	location "FractalViewer"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "FractalViewer/src/pch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src/",
		"%{prj.name}/extlib/glfw/include/",
		"%{prj.name}/extlib/glm/include/"
	}

	libdirs {
		"%{prj.name}/extlib/glfw/"
	}

	links {
		"GLFW",
		"OpenGL32"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines "FV_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "FV_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "FV_DIST"
		optimize "On"
