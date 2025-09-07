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
    static std::unique_ptr<Manager> _instance;


    explicit Manager() noexcept = default;

public:

    static Manager& instance();

    void set_format(const std::string_view format);

    void add_loger(const std::string& name, levels level);

    void remove_logger(const std::string &name);

    std::shared_ptr<Logger> logger(const std::string &name) const;

    ~Manager();
};

#endif //SLOG_MANAGER_H