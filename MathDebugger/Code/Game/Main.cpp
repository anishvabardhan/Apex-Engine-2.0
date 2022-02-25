#include "Framework/App.h"
#include "Engine/Platform/WindowsH.h"
#include "Engine/Core/CoreIncludes.h"

// App Singleton

extern App* g_App;

//------------------------------------------------------------------------------------------------------------------
// Windows Main Function

int WINAPI WinMain( _In_ HINSTANCE applicationInstanceHandle , _In_opt_ HINSTANCE , _In_ LPSTR commandLineString , _In_ int )
{
	// Unused variables
	
	UNUSED( commandLineString );
	UNUSED( applicationInstanceHandle );

	//------------------------------------------------------------------------------------------------------------------
	// Creating App Instance

	g_App = new App();

	//------------------------------------------------------------------------------------------------------------------
	// Starting the App

	g_App->Startup();

	//------------------------------------------------------------------------------------------------------------------
	// App/Game Loop
	
	while (!g_App->IsAppQuitting())
	{
		g_App->RunFrame();
	}

	//------------------------------------------------------------------------------------------------------------------
	// App Shutdown

	g_App->Shutdown();

	//------------------------------------------------------------------------------------------------------------------
	// Deleting App

	if(g_App)
	{
	    delete g_App;
	    g_App = nullptr;
	}

	return 0;
}

//------------------------------------------------------------------------------------------------------------------