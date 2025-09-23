set(CMAKE_CXX_STANDARD 20)
add_executable(format_example main.cpp)
target_link_libraries(format_example slog::slog Dbghelp)