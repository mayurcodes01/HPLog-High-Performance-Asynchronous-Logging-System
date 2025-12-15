#include "logger.hpp"
/*
int main() {
    Logger logger("app.log");

    logger.log(LogLevel::INFO, "Application started");
    logger.log(LogLevel::WARN, "Low memory warning");
    logger.log(LogLevel::ERROR, "Something failed");

    return 0; // RAII flush + clean shutdown
}*/

int main() {
    Logger logger("app.log");

    for (int i = 0; i < 10000; ++i) {
        logger.log(LogLevel::INFO, "High frequency log test");
    }

    return 0;
}
