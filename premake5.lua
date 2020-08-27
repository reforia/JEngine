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

include "JEngine/ThirdParty/GLFW"
include "JEngine/ThirdParty/Glad"
include "JEngine/ThirdParty/imgui"

project "JEngine"
    location "JEngine"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("intermediate/" .. outputdir .. "/%{prj.name}")

    pchheader "JE_PCH.h"
    pchsource "JEngine/src/Private/JE_PCH.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/ThirdParty/glm/glm/**.hpp",
        "%{prj.name}/ThirdParty/glm/glm/**.inl",
    }

    includedirs
    {
        "%{prj.name}/ThirdParty/SpdLog/include",
        "%{prj.name}/src/Public",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.Imgui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Glad",
        "GLFW",
        "Imgui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "JE_PLATFORM_WINDOWS",
            "JE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }

    filter "configurations:Debug"
        defines "JE_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "JE_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Distribution"
        defines "JE_DISTRIBUTION"
        runtime "Release"
        optimize "On"
        
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

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
        "%{IncludeDir.glm}"
    }

    links
    {
        "JEngine"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "JE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "JE_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "JE_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Distribution"
        defines "JE_DISTRIBUTION"
        runtime "Release"
        optimize "On"