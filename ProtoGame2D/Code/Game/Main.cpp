#include "Framework/App.h"

extern App* g_App;

int main()
{
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