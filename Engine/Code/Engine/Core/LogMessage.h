#pragma once

#include "Engine/Core/CoreIncludes.h"

//----------------------------------------------------------------------------------------------------------------------------
// Defining the Logging Checks of all severities

#define LOG_INFO LogMessage(INFO, __FILE__, __LINE__)
#define LOG_WARNING LogMessage(WARNING,__FILE__,__LINE__)
#define LOG_FATAL LogMessageFatal(__FILE__,__LINE__)
#define LOG(severity) LOG_##severity

#define LOG_CHECK(condition) \
	if(!(condition)) LogMessageFatal(__FILE__,__LINE__) << "Check failed: "

//----------------------------------------------------------------------------------------------------------------------------
// Defining the SEVERITY Levels

enum SEVERITY {
	INFO      = 0,
	WARNING   = 1,
	FATAL     = 2
};

//----------------------------------------------------------------------------------------------------------------------------
// Declaring Functions

unsigned int GetMessageBoxIconForSeverity(SEVERITY severity);
bool DebuggerPresent();

String Stringf(const char* messageText, ...);
void Debugf(const char* messageText, ...);
void LogToIDE(const String& msg);

bool MessageOK(const String& messageText, const String& severityName, SEVERITY severity);
bool MessageYesNo(const String& messageText, const String& severityName, SEVERITY severity);

//----------------------------------------------------------------------------------------------------------------------------
// global variables

static const char* SeverityNames[] = { "INFO","WARNING", "FATAL" };

//----------------------------------------------------------------------------------------------------------------------------
// Creating the base Logging Class

class LogMessage : public std::ostringstream 
{
	SEVERITY m_Severity;
	const char* m_FileName;
	int m_Line;
public:				
	LogMessage(SEVERITY severity, const char* fileName = nullptr, int line = 0);
	~LogMessage();
protected:
    void Log(SEVERITY severity);
};

//----------------------------------------------------------------------------------------------------------------------------
// Creating the child class LoggingFatal for fatal severity

class LogMessageFatal : public LogMessage 
{
public:
	LogMessageFatal(const char* fileName, int line);
	~LogMessageFatal();
};