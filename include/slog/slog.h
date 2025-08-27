//
// Created by Maks930 on 08/26/2025.
//

#ifndef SLOG_SLOG_H
#define SLOG_SLOG_H

#include <sstream>

#if (defined(__cplusplus) && __cplusplus >= 202002L)
#include <format>
#endif

/*
 *  LOG Levels
 *  TRACE
 *  INFO
 *  DEBUG
 *  WARNING
 *  ERROR
 *  FATAL/CRITICAL
 */

namespace  slog {

    enum class levels {TRACE = 0, INFO = 1, DEBUG = 2, WARN = 3, ERROR = 4, CRIT = 5};

    class Logger;

    class LogMessage {
    private:
        Logger*             m_pLogger;
        levels              m_level;
        std::stringstream   m_ss;
    public:
        LogMessage(Logger *logger, const slog::levels& level);
        ~LogMessage();

        template <typename T>
        LogMessage& operator<<(const T& msg) {
            m_ss << msg;
            return *this;
        }
    };

    class Logger {
    private:
        std::string m_sName;
        slog::levels m_ignoreConsoleLevel;

        void static setUtcOffset();

    public:
        explicit Logger(std::string name);
        explicit Logger(std::string name, const slog::levels& level);
        static void init(const std::string& filename);
        static void init(const std::string& filename, const slog::levels& level);
        static void flush();

        void log(const slog::levels& level, const std::string& msg) const;

        [[nodiscard]] slog::levels level() const;
        [[nodiscard]] static slog::levels file_level();


        LogMessage info();
        LogMessage debug();
        LogMessage warn();
        LogMessage error();
        LogMessage critical();
        LogMessage trace();

#if (defined(__cplusplus) && __cplusplus >= 202002L)
        template <typename ...Args>
        void info(const std::format_string<Args...> &fmt, Args&&... args) {
            LogMessage(this, levels::INFO) << std::format(fmt, std::forward<Args>(args)...);
        }

        template <typename ...Args>
        void debug(const std::format_string<Args...> &fmt, Args&&... args) {
            LogMessage(this, levels::DEBUG) << std::format(fmt, std::forward<Args>(args)...);
        }

        template <typename ...Args>
        void warn(const std::format_string<Args...> &fmt, Args&&... args) {
            LogMessage(this, levels::WARN) << std::format(fmt, std::forward<Args>(args)...);
        }


        template <typename ...Args>
        void error(const std::format_string<Args...> &fmt, Args&&... args) {
            LogMessage(this, levels::ERROR) << std::format(fmt, std::forward<Args>(args)...);
        }


        template <typename ...Args>
        void critical(const std::format_string<Args...> &fmt, Args&&... args) {
            LogMessage(this, levels::CRIT) << std::format(fmt, std::forward<Args>(args)...);
        }

        template <typename ...Args>
        void trace(const std::format_string<Args...> &fmt, Args&&... args) {
            LogMessage(this, levels::TRACE) << std::format(fmt, std::forward<Args>(args)...);
        }
#endif
    };
};

#endif //SLOG_SLOG_H