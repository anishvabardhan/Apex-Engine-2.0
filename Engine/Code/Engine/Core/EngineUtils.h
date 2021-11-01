#pragma once

#include "LogMessage.h"
#include "Logger.h"

void EngineStartup()
{
	LogStartup();
	LOG_INFO << "Engine Startup!!";
}

void EngineShutdown()
{
	LOG_INFO << "Engine Shutdown!!";
	LogShutdown();
}