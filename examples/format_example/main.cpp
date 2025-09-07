//
// Created by Maks930 on 08/26/2025.
//

#include <thread>
#include <slog/slog.h>


// [{LOG_LEVEL}] {DATE} {TIME}.{UTCOffset} [{LoggerName:>10}]{Message:>10}



int main() {
    // slog::Logger::init("latest.log", slog::levels::DEBUG);
    // auto l = slog::Logger("MAIN", slog::levels::TRACE);
    // l.trace("Hello, C++{}", __cplusplus);
    // l.info("Some message");
    // l.debug("Number: {}", 58);
    // l.warn("Potential error at line {}", __LINE__);
    // l.error("All fine");
    // l.critical("One minute");

    // Logger logger("main_logger", 0);
    // Logger logger2("second_logger", 0);
    //
    // logger.addSink(std::make_shared<FileSink>("./logp.txt"));
    // logger2.addSink(std::make_shared<FileSink>("./logp.txt"));
    //
    // logger.info("Hello, World!");
    // logger2.info("Hello, World!");

    std::thread t1([]() {
        slog::Manager::instance().add_loger("Thread-1", slog::levels::TRACE);
        // LoggerManager::addLoger("Thread-1", 0);
        const std::shared_ptr<slog::Logger> logger = slog::Manager::instance().logger("Thread-1");
        logger->addSink(std::make_shared<slog::sinks::FileSink>("./main.txt"));
        logger->addSink(std::make_shared<slog::sinks::FileSink>("./"+ logger->name() + ".txt"));
        logger->addSink(std::make_shared<slog::sinks::ConsoleSink>());

        logger->trace("Hello, World!, {}", 1); std::this_thread::sleep_for(std::chrono::seconds(1));
        logger->info("Hello, World!, {}", 2); std::this_thread::sleep_for(std::chrono::seconds(2));
        logger->debug("Hello, World!, {}", 3); std::this_thread::sleep_for(std::chrono::seconds(1));
        logger->warning("Hello, World!, {}", 4); std::this_thread::sleep_for(std::chrono::seconds(5));

    });

    std::thread t2([]() {
        slog::Manager::instance().add_loger("Thread-2", slog::levels::TRACE);
        const std::shared_ptr<slog::Logger> logger = slog::Manager::instance().logger("Thread-2");

        logger->addSink(std::make_shared<slog::sinks::FileSink>("./main.txt"));
        logger->addSink(std::make_shared<slog::sinks::FileSink>("./"+ logger->name() + ".txt"));
        logger->addSink(std::make_shared<slog::sinks::ConsoleSink>());

        logger->warning("Hello, World!, {}", 5); std::this_thread::sleep_for(std::chrono::milliseconds(512));
        logger->error("Hello, World!, {}", 6); std::this_thread::sleep_for(std::chrono::seconds(3));
        logger->critical("Hello, World!, {}", 7); std::this_thread::sleep_for(std::chrono::seconds(4));
        logger->info("Hello, World!, {}", 8); std::this_thread::sleep_for(std::chrono::seconds(1));
    });


    t1.join();
    t2.join();

    return 0;
}