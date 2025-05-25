workspace "Kitsune"		-- sln文件名
	architecture "x64"	
	configurations{
		"Debug",
		"Release",
		"Dist"
	}

-- https://github.com/premake/premake-core/wiki/Tokens#value-tokens
-- 组成输出目录:Debug-windows-x86_64
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Kitsune"		--KITSUNE项目
	location "Kitsune"  --在sln所属文件夹下的KITSUNE文件夹
	kind "SharedLib"    --dll动态库
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}") -- 输出目录
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")-- 中间目录

	buildoptions { "/utf-8" }

	-- 包含的所有h和cpp文件
	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	-- 包含目录
	includedirs{
		"%{prj.name}/thirdparty/spdlog/include"
	}
	-- 如果是window系统
	filter "system:windows"
		cppdialect "C++17"
		-- On:代码生成的运行库选项是MTD,静态链接MSVCRT.lib库;
		-- Off:代码生成的运行库选项是MDD,动态链接MSVCRT.dll库;打包后的exe放到另一台电脑上若无这个dll会报错
		staticruntime "On"	
		systemversion "latest"	-- windowSDK版本
		-- 预处理器定义
		defines{
			"KITSUNE_PLATFORM_WINDOWS",
			"KITSUNE_BUILD_DLL"
		}
		-- 编译好后移动Kitsune.dll文件到Sandbox文件夹下
		postbuildcommands{
			("{COPYDIR} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir ..  "/SandBox/\"" )
		}
	-- 不同配置下的预定义不同
	filter "configurations:Debug"
		defines "KITSUNE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "KITSUNE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "KITSUNE_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	buildoptions { "/utf-8" }

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	-- 同样包含spdlog头文件
	includedirs{
		"Kitsune/thirdparty/spdlog/include",
		"Kitsune/src"
	}
	-- 引用Kitsune
	links{
		"Kitsune"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines{
			"KITSUNE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "KITSUNE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "KITSUNE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "KITSUNE_DIST"
		optimize "On"
