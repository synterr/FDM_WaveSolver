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

void Log::Error(const char* message, bool endline)
{
    if (m_LogLevel >= LevelError)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        if (m_newline)
            printf("[ERROR]:");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
        printf(message);

        if (endline)
        {
            printf("\n");
            m_newline = true;
        }
        else
            m_newline = false;
    }
}

void Log::Warn(const char* message, bool endline)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);
    if (m_newline)
        printf("[WARNING]:");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
    printf(message);

    if (endline)
    {
        printf("\n");
        m_newline = true;
    }
    else
        m_newline = false;
    
}

void Log::Info(const char* message, bool endline)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
    if (m_newline)
        printf("[INFO]:");

    printf(message);

    if (endline)
    {
        printf("\n");
        m_newline = true;
    }
    else
        m_newline = false;
    
}
