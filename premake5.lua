workspace "Hazel"		-- sln文件名
	architecture "x64"	
	startproject "Sandbox" -- 启动项目
	configurations{
		"Debug",
		"Release",
		"Dist"
	}
-- https://github.com/premake/premake-core/wiki/Tokens#value-tokens
-- 组成输出目录:Debug-windows-x86_64
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- 包含相对解决方案的目录
includeDir = {}
includeDir["GLFW"] = "Hazel/vendor/GLFW/include"
-- 下面这个 include 相当于把 glfw 库中的 premake.lua 内容拷贝到此处

includeDir["Glad"] = "Hazel/vendor/Glad/include"
includeDir["ImGui"] = "Hazel/vendor/imgui"

group "Dependencies"
	include "Hazel/vendor/imgui"
	include "Hazel/vendor/GLFW"
	include "Hazel/vendor/Glad"
group ""

project "Hazel"		--Hazel项目
	location "Hazel"--在sln所属文件夹下的Hazel文件夹
	kind "SharedLib"--dll动态库
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}") -- 输出目录
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")-- 中间目录

	-- On: 代码生成的时候运行库选项是 MTD，静态链接 MSVCRT.lib 库
	-- Off: 代码生成的运行库选项是 MDD，动态链接 MSVCRT.dll 库；打包到另一台电脑的.exe没有dll文件会报错
	staticruntime "Off"

	-- 预编译头
	pchheader "hzpch.h"
	pchsource "Hazel/src/hzpch.cpp"

	-- 包含的所有h和cpp文件
	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	-- 包含目录
	includedirs{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{includeDir.GLFW}",
		"%{includeDir.Glad}",
		"%{includeDir.ImGui}"
	}

	-- Hazel 链接 glfw 项目
	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	filter "system:windows"
		defines {
			"HZ_PLATFORM_WINDOWS",
			"HZ_ENABLE_ASSERTS"
		}

	-- 如果是window系统
	filter "system:windows"
		cppdialect "C++17"
		systemversion "10.0"	-- windowSDK版本
		-- 预处理器定义
		defines{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL"
		}
		-- 编译好后移动Hazel.dll文件到Sandbox文件夹下
		postbuildcommands{
			-- ("{COPY} %{cfg.buildtarget.relpath} ../bin/".. outputdir .."/Sandbox/")
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/".. outputdir .."/Sandbox/\"")
		}

	-- 不同配置下的预定义不同
	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		-- 如果想要一个非 dll，那么就是 staticruntime，但这里我们还是用dll
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	-- 同样包含spdlog头文件
	includedirs{
		"Hazel/vendor/spdlog/include",
		"Hazel/src"
	}
	-- 引用hazel
	links{
		"Hazel"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines{
			"HZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "On"
