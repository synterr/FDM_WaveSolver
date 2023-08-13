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

void Log::Error(const char* message, bool endline)
{
    if (m_LogLevel >= LevelError)
    {
        if (m_newline) //For errors, always begin from new line!
        {
            printf("\n");
            m_newline = false;
        }
        m_error_cnt++;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
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
    m_warn_cnt++;
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
    m_info_cnt++;
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
