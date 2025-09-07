//
// Created by Maks930 on 09/07/2025.
//

#ifndef SLOG_SINK_H
#define SLOG_SINK_H

#include <sstream>
#include <memory>

namespace slog::sinks {
    class ISink {
    protected:
        std::stringstream m_sstream;
        std::shared_ptr<std::ostream> m_pSink;

    public:
        explicit ISink(std::shared_ptr<std::ostream> sink = nullptr);
        virtual ~ISink() = default;

        void flush();

        template <typename T>
        ISink& operator<<(const T& value) {
            m_sstream << value;
            return *this;
        }
    };
};



#endif //SLOG_SINK_H