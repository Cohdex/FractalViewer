workspace "FractalViewer"
	architecture "x86_64"
	configurations { "Debug", "Develop", "Release" }

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
		"%{prj.name}/extlib/glew/include/",
		"%{prj.name}/extlib/glm/include/"
	}

	libdirs {
		"%{prj.name}/extlib/glfw/",
		"%{prj.name}/extlib/glew/"
	}

	links {
		"GLFW",
		"glew32s",
		"OpenGL32"
	}

	defines {
		"GLEW_STATIC"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines "FV_DEBUG"
		symbols "On"
		optimize "Off"

	filter "configurations:Develop"
		defines "FV_DEVELOP"
		symbols "Off"
		optimize "On"

	filter "configurations:Release"
		defines "FV_RELEASE"
		symbols "Off"
		optimize "Full"
