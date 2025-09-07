//
// Created by Maks930 on 09/07/2025.
//

#ifndef SLOG_LOGMESSAGE_H
#define SLOG_LOGMESSAGE_H

#include <sstream>
#include <slog/levels.h>
#include <chrono>

namespace slog {
    class LogMessage;
}


class slog::LogMessage {
private:
    std::stringstream m_sstream;
    slog::levels log_level;
    std::time_t timestamp;

public:
    LogMessage(const std::string &data, const slog::levels& level);

    explicit LogMessage(const slog::levels& level);

    template <typename T>
    LogMessage& operator<<(const T& value) {
        m_sstream << value;
        return *this;
    }

    std::string str() const;

    slog::levels level() const;
    std::time_t time() const;

    friend class Logger;

};

#endif //SLOG_LOGMESSAGE_H