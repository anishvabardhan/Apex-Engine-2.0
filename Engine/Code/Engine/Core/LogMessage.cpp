#include "LogMessage.h"

#include "Engine/Platform/WindowsH.h"
#include <iostream>
#include "Logger.h"

unsigned int GetMessageBoxIconForSeverity(SEVERITY severity)
{
	switch (severity)
	{
	case WARNING:           return MB_ICONEXCLAMATION;
	case FATAL:             return MB_ICONHAND;
	default:                      return MB_ICONEXCLAMATION;
	}
};

LogMessage::LogMessage(SEVERITY severity, const char* fileName, int line)
	: m_Severity(severity), m_FileName(fileName), m_Line(line)
{
}

   LogMessage::~LogMessage()
{
	Log(m_Severity);
}

void LogMessage::Log(SEVERITY severity)
{
	std::string messageText;

	if (severity == INFO)
	{
		Debugf("\n------------------------------------------------------------------------------\n");
		Debugf("\n[%s]: %s(Line %d): %s\n", SeverityNames[m_Severity], m_FileName, m_Line, str().c_str());
		Debugf("\n------------------------------------------------------------------------------\n");
	}
	else
	{
		bool isDebuggerPresent = (IsDebuggerPresent() == TRUE);

		if (isDebuggerPresent)
		{
			messageText += "\nWould you like to break and debug?\n";
		}

		messageText += Stringf("\n[%s]: %s(Line %d): %s\n", SeverityNames[m_Severity], m_FileName, m_Line, str().c_str());

		Debugf("\n------------------------------------------------------------------------------\n");
		Debugf("\n[%s]: %s(Line %d): %s\n", SeverityNames[m_Severity], m_FileName, m_Line, str().c_str());
		Debugf("\n------------------------------------------------------------------------------\n");

		if (severity == FATAL)
		{
			LOG_INFO << "Engine ShutDown Abruptly!!";
		}

		if (isDebuggerPresent)
		{
			bool isYesNo = MessageYesNo(messageText, SeverityNames[m_Severity], severity);

			LogFLush();

			if (isYesNo)
			{  
				__debugbreak();
			}
		}
		else
		{
			MessageOK(messageText, SeverityNames[m_Severity], severity);
		}
	}
}

LogMessageFatal::LogMessageFatal(const char* fileName, int line)
	: LogMessage(FATAL, fileName, line)
{
}

LogMessageFatal::~LogMessageFatal()
{
	Log(FATAL);
	exit(0);
}

   std::string Stringf(const char* messageText, ...)
{
	char text[2048];
	va_list VAList;
	va_start(VAList, messageText);
	vsnprintf_s(text, 2048, _TRUNCATE, messageText, VAList);
	va_end(VAList);
	text[2047] = '\0';

	return std::string(text);
}

void Debugf(const char* messageText, ...)
{
	char text[2048];
	va_list VAList;
	va_start(VAList, messageText);
	vsnprintf_s(text, 2048, _TRUNCATE, messageText, VAList);
	va_end(VAList);
	text[2047] = '\0';

	LogPrint(text);
}

void LogToIDE(const std::string& msg)
{
	if (DebuggerPresent())
	{
		OutputDebugStringA(msg.c_str());
	}

	std::cout << msg.c_str();
}

bool DebuggerPresent()
{
	typedef BOOL(__stdcall IsAvailable)();

	static HINSTANCE hInstKernel32 = GetModuleHandle(TEXT("KERNEL32"));
	if (!hInstKernel32)
		return false;

	static IsAvailable* isDebuggerPresentFunc = (IsAvailable*)GetProcAddress(hInstKernel32, "IsDebuggerPresent");
	if (!isDebuggerPresentFunc)
		return false;

	static BOOL isDebuggerAvailable = isDebuggerPresentFunc();

	return isDebuggerAvailable == TRUE;
}

bool MessageOK(const std::string& messageText, const std::string& severityName, SEVERITY severity)
{
	bool isOK = true;

	UINT msgIcon = GetMessageBoxIconForSeverity(severity);
	int buttonClicked = MessageBoxA(NULL, messageText.c_str(), severityName.c_str(), MB_OK | msgIcon | MB_TOPMOST);
	isOK = (buttonClicked == IDOK);

	return isOK;
}

bool MessageYesNo(const std::string& messageText, const std::string& severityName, SEVERITY severity)
{
	bool isYes = true;

	UINT msgIcon = GetMessageBoxIconForSeverity(severity);
	int buttonClicked = MessageBoxA(NULL, messageText.c_str(), severityName.c_str(), MB_YESNO | msgIcon | MB_TOPMOST);
	isYes = (buttonClicked == IDYES);

	return isYes;
}