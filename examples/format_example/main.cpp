//
// Created by Maks930 on 08/26/2025.
//

#include <slog/slog.h>

int main() {
    slog::Logger::init("latest.log");
    auto l = slog::Logger("MAIN");
    l.trace("Hello, C++{}", __cplusplus);
    l.info("Some message");
    l.debug("Number: {}", 58);
    l.warn("Potential error at line {}", __LINE__);
    l.error("All fine");
    l.critical("One minute");

    return 0;
}