project "stb"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/%{cfg.architecture}-%{cfg.buildcfg}-%{cfg.system}")
	objdir ("bin-int/%{cfg.architecture}-%{cfg.buildcfg}-%{cfg.system}")

	files {
		"stb_image/**.h",
		"stb_image/**.cpp",
	}