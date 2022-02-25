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
        "BrickBreaker/Data/",
        "MathDebugger/Code/",
        "MathDebugger/Data/"
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