set(CMAKE_CXX_STANDARD 20)
add_executable(multithread_example main.cpp)
target_link_libraries(multithread_example slog::slog)