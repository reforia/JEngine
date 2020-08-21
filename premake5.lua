workspace "JEngine"
    architecture "x64"

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

include "JEngine/ThirdParty/GLFW"

project "JEngine"
    location "JEngine"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

    pchheader "JE_PCH.h"
    pchsource "JEngine/src/Private/JE_PCH.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/ThirdParty/SpdLog/include",
        "%{prj.name}/src/Public",
        "%{IncludeDir.GLFW}"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "JE_PLATFORM_WINDOWS",
            "JE_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "JE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "JE_DEBUG"
        optimize "On"

    filter "configurations:Distribution"
        defines "JE_DISTRIBUTION"
        optimize "On"
        
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

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
        "JEngine/src"
    }

    links
    {
        "JEngine"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "JE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "JE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "JE_RELEASE"
        optimize "On"

    filter "configurations:Distribution"
        defines "JE_DISTRIBUTION"
        optimize "On"