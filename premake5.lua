
workspace "Caster3D"
	architecture "x64"
    flags "MultiProcessorCompile"

	configurations {
		"Debug",
		"Release"
	}

	filter "configurations:Debug"
		optimize "off"
		symbols "on"

	filter "configurations:Release"
		optimize "speed"
		symbols "off"

group "Dependencies"
	include "vendor/stb"
group ""

project "Caster3D"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/%{cfg.architecture}-%{cfg.buildcfg}-%{cfg.system}")
	objdir ("bin-int/%{cfg.architecture}-%{cfg.buildcfg}-%{cfg.system}")

	files {
		"include/**.h",
		"src/**.cpp",
	}

	includedirs {
		"include",
		"vendor/glm",
		"vendor/stb"
	}

	links {
		"stb"
	}
