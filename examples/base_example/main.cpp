//
// Created by Maks930 on 08/26/2025.
//

#include <slog/slog.h>

int main() {
    slog::Logger::init("latest.log");
    auto l = slog::Logger("MAIN");
    l.trace() << "Hello World!";
    l.info() << "Some message";
    l.debug() << "Some debug message";
    l.warn() << "some warning message";
    l.error() << "some error message";
    l.critical() << "some critical message";

    return 0;
}