# SLOG 

## About
Simple logging library. 
The minimum version of the standard required for the library to work is C++20,

## Examples

### C++20 and later
```c++
#include <slog/slog.h>

int main() {
    const auto logger = slog::Manager::instance().add_loger("MAIN");
    logger->addSink(std::make_shared<slog::sinks::ConsoleSink>());
    logger->addSink(std::make_shared<slog::sinks::FileSink>("./latest.log"));

    logger->trace("Hello trace");
    logger->info("Hello info");
    logger->debug("Hello debug");
    logger->warning("Hello warning");
    logger->error("Hello error");
    logger->critical("Hello critical");


    return 0;
}
```

## Add to project

### Subdirectory
```CMake
cmake_minimum_required(VERSION 3.5)
project(test)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(slog)

add_executable(test main.cpp)
target_link_libraries(test slog::slog)
```

### Fetch Content
```CMake
cmake_minimum_required(VERSION 3.5)
project(test)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
  slog
  GIT_REPOSITORY https://github.com/Maks930/slog
  GIT_TAG        v1.0.0
)
FetchContent_MakeAvailable(slog)

add_executable(test main.cpp)
target_link_libraries(test slog::slog)
```
