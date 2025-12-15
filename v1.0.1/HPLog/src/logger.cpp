#include "logger.hpp"
#include <iostream>

Logger::Logger(const char* filename) {
    file.open(filename, std::ios::out | std::ios::app);
    workerThread = std::thread(&Logger::worker, this);
}

Logger::~Logger() {
    running = false;
    cv.notify_all();

    if (workerThread.joinable())
        workerThread.join();

    file.flush();
    file.close();
}

void Logger::log(LogLevel level, const char* msg) {
    {
        std::lock_guard<std::mutex> lock(mtx);
        queue.emplace(level, msg); // move, no heap
    }
    cv.notify_one();
}

void Logger::worker() {
    while (running || !queue.empty()) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&] {
            return !queue.empty() || !running;
            });

        while (!queue.empty()) {
            LogMessage msg = std::move(queue.front());
            queue.pop();
            lock.unlock();

            // minimal formatting
            file << static_cast<int>(msg.level)
                << " : " << msg.text << "\n";

            lock.lock();
        }
    }
}
