#pragma once

#include <string>
#include <queue>
#include <vector>

typedef void (*LogCallback)(const std::string& msg);

//----------------------------------------------------------------------------------------------
// SystemFunctions

void LogStartup();
void LogShutdown();
void LogPrint(const char* format, ...);
void LogFLush();

//----------------------------------------------------------------------------------------------
//Class Declaration

class Logger {
	std::queue<std::string> m_LogQueue;
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
	void AddLogMessage(const std::string& msg);
	void Flush();

	//----------------------------------------------------------------------------------------------
	//Static Methods

	static void LogToFile(const std::string& msg);
	static Logger* CreateInstance();
	static void DestroyInstance();
};