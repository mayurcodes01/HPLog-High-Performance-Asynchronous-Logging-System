#pragma once
#include <chrono>
#include <cstring>

enum class LogLevel {
    INFO,
    WARN,
    ERROR
};

struct LogMessage {
    LogLevel level;
    std::chrono::system_clock::time_point time;
    char text[256];   // fixed-size buffer (no heap)

    LogMessage() = default;

    LogMessage(LogLevel lvl, const char* msg)
        : level(lvl), time(std::chrono::system_clock::now())
    {
        strncpy_s(text, sizeof(text), msg, _TRUNCATE);
    }


    // move-only (important)
    LogMessage(const LogMessage&) = delete;
    LogMessage& operator=(const LogMessage&) = delete;

    LogMessage(LogMessage&&) = default;
    LogMessage& operator=(LogMessage&&) = default;
};
