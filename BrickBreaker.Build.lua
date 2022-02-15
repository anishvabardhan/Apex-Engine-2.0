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