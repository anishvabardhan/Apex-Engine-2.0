#include "Framework/App.h"
#include "Engine/Platform/WindowsH.h"
#include "Engine/Core/CoreIncludes.h"

extern App* g_App;

int WINAPI WinMain( _In_ HINSTANCE applicationInstanceHandle , _In_opt_ HINSTANCE , _In_ LPSTR commandLineString , _In_ int )
{
	UNUSED( commandLineString );
	UNUSED( applicationInstanceHandle );

	g_App = new App();

	g_App->Startup();
	
	while (!g_App->IsAppQuitting())
	{
		g_App->RunFrame();
	}

	g_App->Shutdown();

	delete g_App;
	g_App = nullptr;

	return 0;
}