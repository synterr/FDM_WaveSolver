#include "Log.h"
#include <iostream>
#include <windows.h>

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
        m_error_cnt++;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        printf("[ERROR]:");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
        printf(message);
        printf("\n");

    }
}

void Log::Warn(const char* message)
{
    if (m_LogLevel >= LevelWarning)
    {
        m_warn_cnt++;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);
        printf("[WARNING]:");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
        printf(message);
        printf("\n");
    }
}

void Log::Info(const char* message)
{
    if (m_LogLevel >= LevelInfo)
    {
        m_info_cnt++;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
        printf("[INFO]:");
        printf(message);
        printf("\n");
    }
}
