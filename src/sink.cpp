//
// Created by Maks930 on 09/07/2025.
//

#include <sink.h>
#include <mutex>

std::mutex m_mutex;

using namespace slog::sinks;


ISink::ISink(std::shared_ptr<std::ostream> sink) : m_pSink(std::move(sink))
{}

void ISink::flush() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_pSink) {
        *m_pSink << m_sstream.str();
        m_sstream.str("");
        m_sstream.clear();
    }
    m_pSink->flush();
}
