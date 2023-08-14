#pragma once
#include <iostream>
#include <windows.h>
#include <sstream>


class Log
{
public:
	enum Level
	{
		LevelNone = 0, LevelError, LevelWarning, LevelInfo
	};

	std::stringstream m_stream;

private:
	int m_error_cnt = 0;
	int m_warn_cnt = 0;
	int m_info_cnt = 0;

	int m_LogLevel = LevelInfo;
	bool m_newline = true;

public:
	Log();
	Log(Level level);
	void SetLevel(Level level);

	void Error(const char* message);
	void Warn(const char* message);
	void Info(const char* message);

	~Log();
};


