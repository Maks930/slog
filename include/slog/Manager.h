//
// Created by Maks930 on 09/07/2025.
//

#ifndef SLOG_MANAGER_H
#define SLOG_MANAGER_H


#include <memory>
#include <unordered_map>
#include <ranges>

#include "Logger.h"

namespace slog {
    class Manager;
}

class slog::Manager {
    std::unordered_map<std::string, std::shared_ptr<Logger>> m_loggers;
    std::string_view global_formatter = "[{0}]{6:>10}{1} {2}{3}{6:>10}[{4:<5}]{6:>10}{5}";
    std::vector<std::string> m_level_mappings;
    static std::unique_ptr<Manager> _instance;


    explicit Manager() noexcept {
        m_level_mappings.reserve(6);
        m_level_mappings = {"TRACE", "INFO", "DEBUG", "WARN", "ERROR", "CRIT"};
    }

public:

    static Manager& instance();

    void set_format(std::string_view format);

    std::shared_ptr<Logger> add_loger(const std::string& name, levels level = slog::levels::TRACE);

    void remove_logger(const std::string &name);

    std::string getMapping(const levels& level) const;

    void setMapping(const levels& level, const std::string &name);

    void setAllMappings(const std::vector<std::string>& levels);

    std::shared_ptr<Logger> logger(const std::string &name) const;

    ~Manager();
};

#endif //SLOG_MANAGER_H