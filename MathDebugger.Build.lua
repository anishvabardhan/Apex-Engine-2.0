project "MathDebugger"
    location (ProjectFileDir)
    kind "WindowedApp"
    language "C++"
    cppdialect "C++17"

    targetdir (BinaryDir)
    objdir (IntermediateDir .. "/%{prj.name}")

    files
    {
        "MathDebugger/Code/Game/Framework/**.h",
        "MathDebugger/Code/Game/Framework/**.cpp",
        "MathDebugger/Code/Game/Main.cpp",
        "MathDebugger/Data/Materials/**.xml",
        "MathDebugger/Data/Textures/**.png",
        "MathDebugger/Data/Shaders/**.shader"
    }

    includedirs
    {
        "Engine/Code/",
        "MathDebugger/Code/",
        "MathDebugger/Data/"
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