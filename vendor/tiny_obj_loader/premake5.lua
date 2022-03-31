project "tiny_obj_loader"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/%{cfg.architecture}-%{cfg.buildcfg}-%{cfg.system}")
	objdir ("bin-int/%{cfg.architecture}-%{cfg.buildcfg}-%{cfg.system}")

	files {
		"./**.h",
		"./**.cc",
	}