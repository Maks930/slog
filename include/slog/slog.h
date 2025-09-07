//
// Created by Maks930 on 08/26/2025.
//

#ifndef SLOG_SLOG_H
#define SLOG_SLOG_H

#include <sstream>
#include "levels.h"

#if (defined(__cplusplus) && __cplusplus >= 202002L)
#include <format>
#endif

#include "sink.h"
#include "LogMessage.h"
#include "Logger.h"
#include "Manager.h"

#include <iostream>
#include <fstream>

namespace slog::sinks {
    class ConsoleSink final : public ISink {
    public:
        ConsoleSink();

        ~ConsoleSink() override;
    };


    class FileSink final : public ISink {
        std::string p;
    public:
        explicit FileSink(const std::string& path);

        ~FileSink() override;
    };
};



#endif //SLOG_SLOG_H