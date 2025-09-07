//
// Created by Maks930 on 09/07/2025.
//

#include <iostream>
#include <sstream>
#include <mutex>

#include <Manager.h>

using namespace slog;


std::mutex mutex;
std::unique_ptr<slog::Manager> slog::Manager::_instance;

Manager & Manager::instance() {
    std::lock_guard<std::mutex> lock(mutex);
    if (!_instance) {
        _instance.reset(new Manager());
    }
    return *_instance;
}

void Manager::set_format(const std::string_view format) {
    global_formatter = format;
    for (const auto& val: m_loggers | std::views::values) {
        val->set_format(format);
    }
}

void Manager::add_loger(const std::string& name, levels level) {
    std::lock_guard<std::mutex> lock(mutex);
    m_loggers.emplace(name, std::make_shared<Logger>(name, level, global_formatter));
}

void Manager::remove_logger(const std::string &name) {
    std::lock_guard<std::mutex> lock(mutex);
    m_loggers.erase(name);
}

std::shared_ptr<Logger> Manager::logger(const std::string &name) const {
    return m_loggers.find(name)->second;
}

Manager::~Manager() = default;
