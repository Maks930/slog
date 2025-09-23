//
// Created by Maks930 on 08/26/2025.
//

#include <iostream>
#include <slog/slog.h>

template <typename T>
class SmartPtr {
public:
    explicit SmartPtr(const T& value) noexcept : ptr(new T(value)) {
        slog::Manager::instance().logger("SmartPtr")->trace("Created SmartPtr with value {} at {}", value, static_cast<void*>(ptr));
    }
    ~SmartPtr() {
        if (ptr != nullptr) {
            delete ptr;
            slog::Manager::instance().logger("SmartPtr")->info("Pointer deleted");
        }else {
            slog::Manager::instance().logger("SmartPtr")->debug("Pointer equ nullptr");
        }

    }

    SmartPtr(const SmartPtr<T>& other) : ptr(new T(*other.ptr)) {
        slog::Manager::instance().logger("SmartPtr")->trace("Pointer created from other SmartPointer");
        slog::Manager::instance().logger("SmartPtr")->trace("ptrValue {}, otherPtrAddr {}; thisPtrAddr {};",
            *ptr, static_cast<void*>(other.ptr), static_cast<void*>(ptr));
    }
    SmartPtr& operator=(const SmartPtr<T>& other) {
        if (this != &other) {
            delete ptr;
            ptr = new T(*other.ptr);
            slog::Manager::instance().logger("SmartPtr")->trace("Pointer assigned to other SmartPtr");
            slog::Manager::instance().logger("SmartPtr")->trace("ptrValue {}, otherPtrAddr {}; thisPtrAddr {};",
                *ptr, static_cast<void*>(other.ptr), static_cast<void*>(ptr));
        }
        return *this;
    };
    SmartPtr(SmartPtr<T>&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
        slog::Manager::instance().logger("SmartPtr")->trace("Moved from SmartPtr");
        slog::Manager::instance().logger("SmartPtr")->trace("FROM {} TO {}", static_cast<void*>(&other), static_cast<void*>(ptr));
    }

    T& operator*() const {
        slog::Manager::instance().logger("SmartPtr")->trace("Get");
        return *ptr;
    }

private:
    T* ptr{ nullptr };
};

int main() {
    slog::Manager::instance().add_loger("SmartPtr");
    slog::Manager::instance().logger("SmartPtr")->addSink(std::make_shared<slog::sinks::ConsoleSink>());

    const auto logger = slog::Manager::instance().add_loger("MAIN");
    logger->addSink(std::make_shared<slog::sinks::ConsoleSink>());

    logger->trace("APP Started");

    SmartPtr<int> ptr{1};

    std::cout << *ptr << std::endl;
    *ptr = 42;
    std::cout << *ptr << std::endl;

    SmartPtr<int> ptr2 = ptr;

    std::cout << *ptr2 << std::endl;
    *ptr2 = 13;
    std::cout << *ptr2 << std::endl;

    logger->trace("APP Ended");

    return 0;
}