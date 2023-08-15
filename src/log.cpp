#include "stdafx.h"
#include "Log.h"

Log::Log()
{
	m_LogLevel = Level::LevelInfo;
}

Log::Log(Level level)
{
	m_LogLevel = level;
}

void Log::SetLevel(Level level)
{
	m_LogLevel = level;
}

Log::~Log()
{
	if (m_error_cnt > 0)
	{
		Warn("press enter to exit!");
		std::getchar();
	}
}

void Log::Error(const char* message)
{
	if (m_LogLevel >= LevelError)
	{
		milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		printf("%zd:", ms.count() % 1000000);
		m_error_cnt++;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		printf("[ERRR]:");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
		printf(message);
		printf("\n");
	}
	m_stream = std::stringstream();
}

void Log::Warn(const char* message)
{
	if (m_LogLevel >= LevelWarning)
	{
		milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		printf("%zd:", ms.count() % 1000000);
		m_warn_cnt++;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);
		printf("[WARN]:");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
		printf(message);
		printf("\n");
	}
	m_stream = std::stringstream();
}

void Log::Info(const char* message)
{
	if (m_LogLevel >= LevelInfo)
	{
		milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		printf("%zd:", ms.count() % 1000000);
		m_info_cnt++;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
		printf("[INFO]:");
		printf(message);
		printf("\n");
	}
	m_stream = std::stringstream();
}
