//
// Created by Maks930 on 08/26/2025.
//

#include <iostream>
#include <slog/slog.h>

template <typename T>
class SmartPtr {
public:
    explicit SmartPtr(const T& value) noexcept : ptr(new T(value)) {
        slog::Logger("SmartPtr").trace("Created SmartPtr with value {} at {}", value, static_cast<void*>(ptr));
    }
    ~SmartPtr() {
        if (ptr != nullptr) {
            delete ptr;
            slog::Logger("~SmartPtr").info("Pointer deleted");
        }else {
            slog::Logger("~SmartPtr").debug("Pointer equ nullptr");
        }

    }

    SmartPtr(const SmartPtr<T>& other) : ptr(new T(*other.ptr)) {
        slog::Logger("SmartPtr").trace("Pointer created from other SmartPointer");
        slog::Logger("SmartPtr").trace("ptrValue {}, otherPtrAddr {}; thisPtrAddr {};",
            *ptr, static_cast<void*>(other.ptr), static_cast<void*>(ptr));
    }
    SmartPtr& operator=(const SmartPtr<T>& other) {
        if (this != &other) {
            delete ptr;
            ptr = new T(*other.ptr);
            slog::Logger("SmartPtr").trace("Pointer assigned to other SmartPtr");
            slog::Logger("SmartPtr").trace("ptrValue {}, otherPtrAddr {}; thisPtrAddr {};",
                *ptr, static_cast<void*>(other.ptr), static_cast<void*>(ptr));
        }
        return *this;
    };
    SmartPtr(SmartPtr<T>&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
        slog::Logger("SmartPtr").trace("Moved from SmartPtr");
        slog::Logger("SmartPtr").trace("FROM {} TO {}", static_cast<void*>(&other), static_cast<void*>(ptr));
    }

    T& operator*() const {
        slog::Logger("SmartPtr").trace("Get");
        return *ptr;
    }

private:
    T* ptr{ nullptr };
};

int main() {
    slog::Logger::init("smartPointer.log");
    slog::Logger("MAIN").trace("APP Started");

    SmartPtr<int> ptr{1};

    std::cout << *ptr << std::endl;
    *ptr = 42;
    std::cout << *ptr << std::endl;

    SmartPtr<int> ptr2 = ptr;

    std::cout << *ptr2 << std::endl;
    *ptr2 = 13;
    std::cout << *ptr2 << std::endl;

    slog::Logger("MAIN").trace("APP Ended");

    return 0;
}