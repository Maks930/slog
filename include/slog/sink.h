//
// Created by Maks930 on 09/07/2025.
//

#ifndef SLOG_SINK_H
#define SLOG_SINK_H

#include <sstream>
#include <memory>
#include <optional>

#include "LogMessage.h"

namespace slog {
    enum class levels;
}

namespace slog::sinks {
    class ISink {
    protected:
        std::stringstream m_sstream;
        levels m_message_level;
        std::optional<levels> m_level = std::nullopt;
        std::shared_ptr<std::ostream> m_pSink;
        std::mutex m_mutex;

    public:
        explicit ISink(std::shared_ptr<std::ostream> sink = nullptr);
        explicit ISink(std::shared_ptr<std::ostream> sink, const levels& level);
        virtual ~ISink() = default;

        virtual void flush();



        template <typename T>
        ISink& operator<<(const T& value) {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_sstream << value;
            return *this;
        }

        virtual void setMessageLevel(slog::levels level);
        std::optional<levels> getSinkLevel() const;
    };
};



#endif //SLOG_SINK_H