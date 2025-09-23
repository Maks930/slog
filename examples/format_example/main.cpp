//
// Created by Maks930 on 08/26/2025.
//

#include <thread>
#include <slog/slog.h>


// [{LOG_LEVEL}] {DATE} {TIME}.{UTCOffset} [{LoggerName:>10}]{Message:>10}

int main() {

    const auto logger = slog::Manager::instance().add_loger("Thread-1");


    logger->addSink(std::make_shared<slog::sinks::ConsoleSink>());

    logger->trace("Hello, World!, {}", 1);
    logger->info("Hello, World!, {}", 2);
    logger->debug("Hello, World!, {}", 3);
    logger->warning("Hello, World!, {}", 5);
    logger->error("Hello, World!, {}", 6);
    logger->critical("Hello, World!, {}", 7);

    return 0;
}