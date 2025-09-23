//
// Created by Maks930 on 08/26/2025.
//

#include <slog/slog.h>

int main() {
    const auto logger = slog::Manager::instance().add_loger("MAIN");
    logger->addSink(std::make_shared<slog::sinks::ConsoleSink>());
    logger->addSink(std::make_shared<slog::sinks::FileSink>("./latest.log"));

    logger->trace("Hello trace");
    logger->info("Hello info");
    logger->debug("Hello debug");
    logger->warning("Hello warning");
    logger->error("Hello error");
    logger->critical("Hello critical");


    return 0;
}