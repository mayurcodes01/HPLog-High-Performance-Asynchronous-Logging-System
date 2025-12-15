#pragma once
#include "log_message.hpp"
#include <atomic>
#include <condition_variable>
#include <fstream>
#include <mutex>
#include <queue>
#include <thread>

class Logger {
public:
    explicit Logger(const char* filename);
    ~Logger(); // RAII cleanup

    void log(LogLevel level, const char* msg);

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    void worker();

    std::ofstream file;
    std::queue<LogMessage> queue;

    std::mutex mtx;
    std::condition_variable cv;
    std::thread workerThread;
    std::atomic<bool> running{ true };
};
