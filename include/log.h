#pragma once

class Log
{
public:
    enum Level
    {
        LevelError = 0, LevelWarning, LevelInfo
    };

private:
    int m_LogLevel = LevelInfo;
    bool m_newline = true;

public:
    Log();
    Log(Level level);
    void SetLevel(Level level);

    void Error(const char* message, bool endline = true);
    void Warn(const char* message, bool endline = true);
    void Info(const char* message, bool endline = true);

};


