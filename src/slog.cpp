//
// Created by Maks930 on 08/26/2025.
//

#include <slog.h>

slog::sinks::ConsoleSink::ConsoleSink(): ISink(std::shared_ptr<std::ostream>(&std::cout, [](std::ostream* os) {})) {
}

slog::sinks::ConsoleSink::~ConsoleSink() = default;

slog::sinks::FileSink::FileSink(const std::string& path): ISink() {
    p = path;
    m_pSink = std::make_shared<std::ofstream>(path, std::ofstream::out | std::ofstream::app);
}

slog::sinks::FileSink::~FileSink() = default;
