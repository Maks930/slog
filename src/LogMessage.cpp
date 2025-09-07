//
// Created by Maks930 on 09/07/2025.
//

#include <LogMessage.h>

slog::LogMessage::LogMessage(const std::string &data, const slog::levels& level) : timestamp(std::time(nullptr)) {
    log_level = level;
    m_sstream << data;
}

slog::LogMessage::LogMessage(const slog::levels& level) : timestamp(std::time(nullptr)) {
    log_level = level;
};

std::string slog::LogMessage::str() const {
    return m_sstream.str();
}

slog::levels slog::LogMessage::level() const {
    return log_level;
}

std::time_t slog::LogMessage::time() const {
    return timestamp;
}
