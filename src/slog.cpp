//
// Created by Maks930 on 08/26/2025.
//

#include <slog.h>

#include <fstream>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <utility>
#include <mutex>

static std::ofstream logfile;
static std::string utcOffset;
static int modLen = 15;
static std::mutex mutex;
static auto ignoreFileLevel{slog::levels::TRACE};

void log_write(const slog::levels& level, const std::string& filename, const std::string& msg, const slog::levels& ignoreConsoleLevel = slog::levels::TRACE);

slog::LogMessage::LogMessage(Logger *logger, const slog::levels& level) : m_pLogger(logger), m_level(level)
{}

slog::LogMessage::~LogMessage() {
    m_pLogger->log(m_level, m_ss.str());
}

void slog::Logger::setUtcOffset() {
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
    utcOffset = ss.str();
}

slog::Logger::Logger(std::string name) : m_sName(std::move(name)) {
    m_ignoreConsoleLevel = slog::levels::TRACE;
}

slog::Logger::Logger(std::string name, const slog::levels &level) : m_sName(std::move(name)) {
    m_ignoreConsoleLevel = level;
}


void slog::Logger::init(const std::string &filename) {
    logfile.open(filename, std::ios::out | std::ios::app);
    setUtcOffset();
}

void slog::Logger::init(const std::string &filename, const slog::levels &level) {
    ignoreFileLevel = level;
    logfile.open(filename, std::ios::out | std::ios::app);
    setUtcOffset();
}


void slog::Logger::flush() {
    std::lock_guard<std::mutex> lock(mutex);
    logfile.flush();
}


void slog::Logger::log(const slog::levels &level, const std::string &msg) const {
    if (utcOffset.empty()) {
        setUtcOffset();
    }
    log_write(level, m_sName, msg, this->m_ignoreConsoleLevel);
}

slog::levels slog::Logger::level() const {
    return m_ignoreConsoleLevel;
}

slog::levels slog::Logger::file_level() {
    return ignoreFileLevel;
}

void log_write(const slog::levels& level, const std::string& filename, const std::string& msg, const slog::levels& ignoreConsoleLevel) {
    if (level < ignoreFileLevel && level < ignoreConsoleLevel) {
        return;
    }

    std::stringstream ss;

    const std::time_t tm = std::time(nullptr);
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()) % 1000;


    std::string logLevel;
    switch (level) {
        case slog::levels::INFO:
            logLevel = "INFO";
            break;
        case slog::levels::DEBUG:
            logLevel = "DEBUG";
            break;
        case slog::levels::WARN:
            logLevel = "WARN";
            break;
        case slog::levels::ERROR:
            logLevel = "ERROR";
            break;
        case slog::levels::CRIT:
            logLevel = "CRITICAL";
            break;
        default:
            logLevel = "TRACE";
            break;
    }
    ss << "[" << logLevel << "]" << std::setfill(' ') << std::setw(modLen - logLevel.size()+2);

    ss << " " << std::put_time(std::localtime(&tm), "%Y/%m/%d  %H:%M:%S");
    ss << "." << std::setfill('0') << std::setw(3) << ms.count();
    ss << utcOffset << " [" << std::setfill(' ') << std::setw(modLen) << filename << "] ";
    ss << msg;

    {
        std::lock_guard<std::mutex> lock(mutex);
        const auto str = ss.str();
        if (logfile.good() && level >= ignoreFileLevel) {
            logfile << str << "\n";
            logfile.flush();
        }

        if (level >= ignoreConsoleLevel) {
            std::cout << str << std::endl;
        }
    }
}

slog::LogMessage slog::Logger::info() { return LogMessage(this, slog::levels::INFO); }
slog::LogMessage slog::Logger::debug() { return LogMessage(this, slog::levels::DEBUG); };
slog::LogMessage slog::Logger::warn() { return LogMessage(this, slog::levels::WARN); };
slog::LogMessage slog::Logger::error() { return LogMessage(this, slog::levels::ERROR); };
slog::LogMessage slog::Logger::critical() { return LogMessage(this, slog::levels::CRIT); };
slog::LogMessage slog::Logger::trace() { return LogMessage(this, slog::levels::TRACE); }