#include "Code/Game.h"
#include "Engine/Core/EngineUtils.h"

int main()
{
	EngineStartup();

	Game* Astroids = new Game();

	Astroids->BeginPlay();

	Astroids->Tick();

	delete Astroids;

	EngineShutdown();

	return 0;
}