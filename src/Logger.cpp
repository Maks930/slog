//
// Created by Maks930 on 09/07/2025.
//

#include <iostream>


#include <Logger.h>

constexpr std::string fr(std::string_view rt_fmt_str, auto&&... args)
{
    return std::vformat(rt_fmt_str, std::make_format_args(args...));
}


std::string level_mappings[6] = {"TRACE", "INFO", "DEBUG", "WARN", "ERROR", "CRIT"};



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

void slog::Logger::addSink(std::shared_ptr<sinks::ISink> sink) {
    m_sinks.push_back(std::move(sink));
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

    std::string a = level_mappings[static_cast<int>(msg.level())];
    return fr(_format, a, date, time, "+0300", m_name, msg.str(), " ") + "\n";
}

void slog::Logger::set_format(const std::string_view format) {
    _format = format;
}

void slog::Logger::write(const slog::levels &level, const std::string &message) {
    slog::LogMessage msg(level); msg << message;
    for (const auto& sink : m_sinks) {
        *sink << format(msg);
        sink->flush();
    }
}
