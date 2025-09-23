//
// Created by Maks930 on 09/07/2025.
//

#include <iostream>
#include <Logger.h>

#include "Manager.h"

constexpr std::string fr(std::string_view rt_fmt_str, auto&&... args)
{
    return std::vformat(rt_fmt_str, std::make_format_args(args...));
}

slog::Logger::Logger(std::string name, const levels& level):
    m_name(std::move(name)), m_level(level)
{}

slog::Logger::Logger(std::string name, const levels& level, const std::string_view format) :
    m_name(std::move(name)), m_level(level), _format(format)
{}

slog::Logger::~Logger() = default;

std::string slog::Logger::name() const {
    return m_name;
}

void slog::Logger::set_level(const levels &level) {
    m_level = level;
}

void slog::Logger::addSink(std::shared_ptr<sinks::ISink> sink) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_sinks.push_back(std::move(sink));
}

std::string getUTCOffset() {
    std::stringstream ss;
    const std::time_t tm = std::time(nullptr);
    const auto local_time = std::mktime(std::localtime(&tm));
    const auto gmt_time = std::mktime(std::gmtime(&tm));

    const int offset_sec = static_cast<int>(std::difftime(local_time, gmt_time));
    const int hh = offset_sec / 3600;
    const int mm = (offset_sec % 3600) / 60;

    ss << (hh >= 0 ? "+": "-" );
    ss << std::setfill('0') << std::setw(2) << hh;
    ss << std::setfill('0') << std::setw(2) << mm;
    return ss.str();
}

std::string slog::Logger::format(const LogMessage& msg) {
    std::stringstream ss;
    const auto msg_time = msg.time();

    ss << " " << std::put_time(std::localtime(&msg_time), "%Y/%m/%d");
    std::string date = ss.str();
    ss.str("");
    ss.clear();
    ss << " " << std::put_time(std::localtime(&msg_time), "%H:%M:%S");
    std::string time = ss.str();

    std::string level_string = Manager::instance().getMapping(msg.level());
    return fr(_format, level_string, date, time, getUTCOffset(), m_name, msg.str(), " ") + "\n";
}

void slog::Logger::set_format(const std::string_view format) {
    _format = format;
}

void slog::Logger::write(const slog::levels &level, const std::string &message) {
    std::lock_guard<std::mutex> lock(m_mutex);
    slog::LogMessage msg(level); msg << message;

    for (const auto& sink : m_sinks) {
        if (!sink->getSinkLevel().has_value() && level >= m_level) {
            *sink << format(msg);
            sink->setMessageLevel(level);
        } else if (level >= sink->getSinkLevel().value()) {
            *sink << format(msg);
            sink->setMessageLevel(level);
        }
        sink->flush();
    }
}
