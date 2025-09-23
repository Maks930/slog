//
// Created by Maks930 on 09/07/2025.
//

#include <sink.h>
#include <mutex>

using namespace slog::sinks;

ISink::ISink(std::shared_ptr<std::ostream> sink) : m_pSink(std::move(sink))
{}

ISink::ISink(std::shared_ptr<std::ostream> sink, const levels &level)
    : m_pSink(std::move(sink)), m_level(level)
{
}

void ISink::flush() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_pSink) {
        *m_pSink << m_sstream.str();
        m_sstream.str("");
        m_sstream.clear();
    }
    m_pSink->flush();
}

void ISink::setMessageLevel(const slog::levels level) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_message_level = level;
}

std::optional<slog::levels> ISink::getSinkLevel() const {
    if (m_level.has_value()) return m_level.value();
    return std::nullopt;
}
