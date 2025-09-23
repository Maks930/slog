//
// Created by Maks930 on 09/07/2025.
//

#include <iostream>
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
    std::lock_guard<std::mutex> lock(mutex);
    global_formatter = format;
    for (const auto& val: m_loggers | std::views::values) {
        val->set_format(format);
    }
}

std::shared_ptr<Logger> Manager::add_loger(const std::string& name, levels level) {
    std::lock_guard<std::mutex> lock(mutex);
    m_loggers.emplace(name, std::make_shared<Logger>(name, level, global_formatter));
    return m_loggers.at(name);
}

void Manager::remove_logger(const std::string &name) {
    std::lock_guard<std::mutex> lock(mutex);
    m_loggers.erase(name);
}

std::string Manager::getMapping(const levels &level) const {
    return m_level_mappings.at(static_cast<size_t>(level));
}

void Manager::setMapping(const levels &level, const std::string &name) {
    m_level_mappings[static_cast<size_t>(level)] = name;
}

void Manager::setAllMappings(const std::vector<std::string> &levels) {
    m_level_mappings.clear();
    m_level_mappings.reserve(static_cast<size_t>(levels.size()));
    m_level_mappings = levels;

}

std::shared_ptr<Logger> Manager::logger(const std::string &name) const {
    std::lock_guard<std::mutex> lock(mutex);
    if (!m_loggers.contains(name)) return nullptr;
    return m_loggers.find(name)->second;
}

Manager::~Manager() = default;
