workspace "BrickBreaker"
    configurations {"Debug", "Development", "Shipping"}
    architecture "x64"
    startproject "BrickBreaker"
    warnings "Extra"

    disable warnings
    {
    	"4100"
    }

BinariesDir = "%{wks.location}/Run/"
IntermediateDir = "%{wks.location}/Temporary/"
EngineFileDir = "%{wks.location}/Engine/Code/"
ProjectFileDir = "%{wks.location}/Temporary/" .. "ProjectFiles/"

ThirdPartyDirs = {
    EngineFileDir .. "External/"
}

    flags
    {
    	"FatalWarnings"
    }

    filter "action:VS*" -- MSVC does not update __cplusplus macro by default
	    	buildoptions { "/Zc:__cplusplus" }

project "Engine"
    location (EngineFileDir .. "Engine/")
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir (BinariesDir)
    objdir (IntermediateDir .. "/%{wks.name}_%{cfg.architecture}_%{cfg.buildcfg}")

    files
    {
    	"**.h",
        "**.cpp"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Development"
        runtime "Release"
        optimize "on"
        symbols "on"

    filter "configurations:Shipping"
        runtime "Release"
        optimize "on"

project "BrickBreaker"
    location (ProjectFileDir)
    kind "WindowedApp"
    language "C++"
    cppdialect "C++17"

    targetdir (BinariesDir)
    objdir (IntermediateDir .. "/%{wks.name}_%{cfg.architecture}_%{cfg.buildcfg}")

    files
    {
        "Code/**.h",
        "Code/**.cpp",
        "Framework/**.h",
        "Framework/**.cpp"
        "Main.cpp"
    }

    includedirs
    {
        EngineFileDir .. "Engine/"
    }

    links 
    {
        "Engine"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Development"
        runtime "Release"
        optimize "on"
        symbols "on"

    filter "configurations:Shipping"
        runtime "Release"
        optimize "on"