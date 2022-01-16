workspace "BrickBreaker"
    configurations {"Debug", "Development", "Shipping"}
    architecture "x64"
    startproject "BrickBreaker"
    warnings "Extra"
    location ("BrickBreaker/")

    disablewarnings
    {
    	"4100"
    }

BinaryDir="%{wks.location}/Run/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/"
IntermediateDir="%{wks.location}/Temporary/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/"
ProjectFileDir="%{wks.location}/Temporary/" .. "ProjectFiles/"
EngineSrcDir="Engine/Code/"

    flags
    {
    	"FatalWarnings"
    }

    filter "action:VS*" -- MSVC does not update __cplusplus macro by default
	    	buildoptions { "/Zc:__cplusplus" }

project "Engine"
    location (EngineSrcDir)
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir (BinaryDir)
    objdir (IntermediateDir .. "/%{prj.name}")

    files
    {
    	"Engine/**.h",
        "Engine/**.cpp"
    }

    includedirs
    {
        "Engine/Code/",
        "BrickBreaker/Code/",
        "BrickBreaker/Data/"
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

    targetdir (BinaryDir)
    objdir (IntermediateDir .. "/%{prj.name}")

    files
    {
        "BrickBreaker/Code/Game/Code/**.h",
        "BrickBreaker/Code/Game/Code/**.cpp",
        "BrickBreaker/Code/Game/Framework/**.h",
        "BrickBreaker/Code/Game/Framework/**.cpp",
        "BrickBreaker/Code/Game/Main.cpp",
        "BrickBreaker/Data/Materials/**.xml",
        "BrickBreaker/Data/Textures/**.png",
        "BrickBreaker/Data/Shaders/**.shader"
    }

    includedirs
    {
        "Engine/Code/",
        "BrickBreaker/Code/",
        "BrickBreaker/Data/"
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