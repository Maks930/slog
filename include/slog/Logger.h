//
// Created by Maks930 on 09/07/2025.
//

#ifndef SLOG_LOGGER_H
#define SLOG_LOGGER_H

#include <string>
#include <memory>
#include <vector>

#include <chrono>
#include <format>

#include "sink.h"
#include "LogMessage.h"


namespace slog {
    class Logger;
}

class slog::Logger {
private:
    std::string m_name;
    std::vector<std::shared_ptr<sinks::ISink>> m_sinks;
    levels m_level;
    std::mutex m_mutex;

    std::string_view _format;

public:
    explicit Logger(std::string name, const levels& level);

    explicit Logger(std::string name, const levels& level, std::string_view format);

    ~Logger();

    [[nodiscard]] std::string name() const;

    void set_level(const levels& level);

    void addSink(std::shared_ptr<sinks::ISink> sink);

    std::string format(const LogMessage& msg);

    void set_format(std::string_view format);

    void write(const slog::levels& level, const std::string& message);

    template <typename ...Args>
    void trace(const std::format_string<Args...> &fmt, Args&&... args) {
        write(slog::levels::TRACE, std::format(fmt, std::forward<Args>(args)...));
    }

    template <typename ...Args>
    void info(const std::format_string<Args...> &fmt, Args&&... args) {
        write(slog::levels::INFO, std::format(fmt, std::forward<Args>(args)...));
    }

    template <typename ...Args>
    void debug(const std::format_string<Args...> &fmt, Args&&... args) {
        write(slog::levels::DEBUG, std::format(fmt, std::forward<Args>(args)...));
    }

    template <typename ...Args>
    void warning(const std::format_string<Args...> &fmt, Args&&... args) {
        write(slog::levels::WARN, std::format(fmt, std::forward<Args>(args)...));
    }

    template <typename ...Args>
    void error(const std::format_string<Args...> &fmt, Args&&... args) {
        write(slog::levels::ERROR, std::format(fmt, std::forward<Args>(args)...));
    }

    template <typename ...Args>
    void critical(const std::format_string<Args...> &fmt, Args&&... args) {
        write(slog::levels::CRIT, std::format(fmt, std::forward<Args>(args)...));
    }

};

#endif //SLOG_LOGGER_H