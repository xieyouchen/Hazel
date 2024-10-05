project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	includedirs {
		"include" -- 为了glad.c直接#include <glad/glad.h>，而不用#include <include/glad/glad.h>
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"