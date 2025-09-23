//
// Created by Maks930 on 08/26/2025.
//

#include <slog.h>

#include <iostream>
#include <fstream>

#define T_COLOR
#define I_COLOR
#define D_COLOR "\e[1;35m"
#define W_COLOR "\e[1;33m"
#define C_COLOR "\033[31m"
#define E_COLOR "\e[1;31m"

slog::sinks::ConsoleSink::ConsoleSink(): ISink(std::shared_ptr<std::ostream>(&std::cout, [](std::ostream* os) {})) {
}

slog::sinks::ConsoleSink::ConsoleSink(const levels &level)
    : ISink(std::shared_ptr<std::ostream>(&std::cout, [](std::ostream* os) {}), level)
{}

slog::sinks::ConsoleSink::~ConsoleSink() = default;

slog::sinks::ColorSink::ColorSink(): ISink(std::shared_ptr<std::ostream>(&std::cout, [](std::ostream* os) {})) {}

slog::sinks::ColorSink::ColorSink(const levels &level)
    : ISink(std::shared_ptr<std::ostream>(&std::cout, [](std::ostream* os) {}), level) {}

slog::sinks::ColorSink::~ColorSink() = default;

void slog::sinks::ColorSink::flush() {
    switch (m_message_level) {
        case levels::DEBUG: *m_pSink << D_COLOR; break;
        case levels::WARN: *m_pSink << W_COLOR; break;
        case levels::ERROR: *m_pSink << E_COLOR; break;
        case levels::CRIT: *m_pSink << C_COLOR; break;
        default: *m_pSink << "\e[1;37m"; break;
    }
    ISink::flush();
}

slog::sinks::FileSink::FileSink(const std::string& path): ISink() {
    p = path;
    m_pSink = std::make_shared<std::ofstream>(path, std::ofstream::out | std::ofstream::app);
}

slog::sinks::FileSink::FileSink(const std::string &path, const levels &level) : ISink(nullptr, level) {
    p = path;
    m_pSink = std::make_shared<std::ofstream>(path, std::ofstream::out | std::ofstream::app);
}

slog::sinks::FileSink::~FileSink() = default;
