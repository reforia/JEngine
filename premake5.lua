workspace "JEngine"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include dirs relative to root folder (solution dir)
IncludeDir = {}
IncludeDir["GLFW"] = "JEngine/ThirdParty/GLFW/include"
IncludeDir["Glad"] = "JEngine/ThirdParty/Glad/include"
IncludeDir["Imgui"] = "JEngine/ThirdParty/imgui"
IncludeDir["glm"] = "JEngine/ThirdParty/glm"
IncludeDir["stb_image"] = "JEngine/ThirdParty/StbImage"

include "JEngine/ThirdParty/GLFW"
include "JEngine/ThirdParty/Glad"
include "JEngine/ThirdParty/imgui"

project "JEngine"
    location "JEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

    pchheader "JE_PCH.h"
    pchsource "JEngine/src/Private/JE_PCH.cpp"

    files
    {
        "%{prj.name}/src/Public/**.h",
        "%{prj.name}/src/Private/**.cpp",
        "%{prj.name}/src/**.h",
        "%{prj.name}/ThirdParty/StbImage/**.cpp",
        "%{prj.name}/ThirdParty/StbImage/**.h",
        "%{prj.name}/ThirdParty/glm/glm/**.hpp",
        "%{prj.name}/ThirdParty/glm/glm/**.inl",
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/ThirdParty/SpdLog/include",
        "%{prj.name}/src/Public",
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.Imgui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    links
    {
        "Glad",
        "GLFW",
        "Imgui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "JE_PLATFORM_WINDOWS",
            "JE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "JE_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "JE_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Distribution"
        defines "JE_DISTRIBUTION"
        runtime "Release"
        optimize "on"
        
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "JEngine/ThirdParty/SpdLog/include",
        "JEngine/src",
        "JEngine/src/Public",
        "JEngine/ThirdParty",
        "%{IncludeDir.glm}"
    }

    links
    {
        "JEngine"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "JE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "JE_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "JE_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Distribution"
        defines "JE_DISTRIBUTION"
        runtime "Release"
        optimize "on"