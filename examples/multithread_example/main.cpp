//
// Created by Maks930 on 08/26/2025.
//

#include <thread>
#include <chrono>
#include <slog/slog.h>



int main() {

    auto file_sink = std::make_shared<slog::sinks::FileSink>("main.log");

    std::thread t1([&file_sink]() {

        const auto logger = slog::Manager::instance().add_loger("Thread-1");

        logger->addSink(std::make_shared<slog::sinks::ConsoleSink>());
        logger->addSink(file_sink);
        logger->addSink(std::make_shared<slog::sinks::FileSink>("thread1.log"));


        logger->trace("Hello, World!, {}", 1); std::this_thread::sleep_for(std::chrono::seconds(1));
        logger->info("Hello, World!, {}", 2); std::this_thread::sleep_for(std::chrono::seconds(2));
        logger->debug("Hello, World!, {}", 3); std::this_thread::sleep_for(std::chrono::seconds(1));
        logger->warning("Hello, World!, {}", 4); std::this_thread::sleep_for(std::chrono::seconds(5));
    });

    std::thread t2([&file_sink]() {
        const auto logger = slog::Manager::instance().add_loger("Thread-2", slog::levels::TRACE);

        logger->addSink(std::make_shared<slog::sinks::ConsoleSink>());
        logger->addSink(file_sink);
        logger->addSink(std::make_shared<slog::sinks::FileSink>("thread2.log"));

        logger->warning("Hello, World!, {}", 5); std::this_thread::sleep_for(std::chrono::milliseconds(512));
        logger->error("Hello, World!, {}", 6); std::this_thread::sleep_for(std::chrono::seconds(3));
        logger->critical("Hello, World!, {}", 7); std::this_thread::sleep_for(std::chrono::seconds(4));
        logger->info("Hello, World!, {}", 8); std::this_thread::sleep_for(std::chrono::seconds(1));
    });

    t1.join();
    t2.join();

    return 0;
}
