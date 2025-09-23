//
// Created by Maks930 on 08/26/2025.
//

#ifndef SLOG_SLOG_H
#define SLOG_SLOG_H

#include <format>

#include "levels.h"
#include "sink.h"
#include "Logger.h"
#include "Manager.h"

namespace slog::sinks {
    class ConsoleSink final : public ISink {
    public:
        ConsoleSink();
        explicit ConsoleSink(const levels &level);

        ~ConsoleSink() override;
    };

    class ColorSink final : public ISink {
    public:
        ColorSink();
        explicit ColorSink(const levels& level);
        ~ColorSink() override;

        void flush() override;
    };

    class FileSink final : public ISink {
        std::string p;
    public:
        explicit FileSink(const std::string& path);
        explicit FileSink(const std::string& path, const levels& level);

        ~FileSink() override;
    };
};



#endif //SLOG_SLOG_H