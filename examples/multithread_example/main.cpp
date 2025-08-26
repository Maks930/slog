//
// Created by Maks930 on 08/26/2025.
//

#include <thread>
#include <chrono>
#include <slog/slog.h>

void task1() {
    auto l = slog::Logger("TASK-1");
    l.trace("Logger created");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    l.info("Prev message have level trace");
    std::this_thread::sleep_for(std::chrono::seconds(5));
    l.debug("Prev message have level debug");
    std::this_thread::sleep_for(std::chrono::seconds(12));
    l.warn("Potential error");
    std::this_thread::sleep_for(std::chrono::seconds(3));
    l.error("Not critical error");
    std::this_thread::sleep_for(std::chrono::seconds(4));
    l.critical("Critical error");
}

void task2() {
    auto l = slog::Logger("TASK-2");
    l.trace("task 2 started");
    std::this_thread::sleep_for(std::chrono::seconds(5));
    l.info("Thread sleep 5 sec");
    std::this_thread::sleep_for(std::chrono::seconds(8));
    l.debug("This message debug");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    l.warn("Zero division");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    l.error("Index out of range");
    std::this_thread::sleep_for(std::chrono::seconds(6));
    l.critical("runtime error");
}

int main() {

    slog::Logger("MAIN").trace("START EXAMPLE");
    std::thread t1(task1);
    std::thread t2(task2);

    t1.join();
    t2.join();

    return 0;
}
