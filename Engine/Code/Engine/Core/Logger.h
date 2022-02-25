#pragma once

#include "Engine/Core/CoreIncludes.h"

typedef void (*LogCallback)(const String& msg);

//----------------------------------------------------------------------------------------------
// SystemFunctions

void LogStartup();
void LogShutdown();
void LogPrint(const char* format, ...);
void LogFlush();

//----------------------------------------------------------------------------------------------
//Class Declaration

class Logger {
	std::queue<String> m_LogQueue;
	std::vector<LogCallback> m_Sinks;
public:
	//----------------------------------------------------------------------------------------------
	//Constructors/Destructors

	Logger();
	~Logger(); 

	//----------------------------------------------------------------------------------------------
	//Methods

	void AddSink(LogCallback cb);
	void RemoveSink(LogCallback cb);
	void AddLogMessage(const String& msg);
	void Flush();

	//----------------------------------------------------------------------------------------------
	//Static Methods

	static void LogToFile(const String& msg);
	static Logger* CreateInstance();
	static void DestroyInstance();
};