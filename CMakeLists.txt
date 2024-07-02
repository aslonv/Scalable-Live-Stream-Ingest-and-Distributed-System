cmake_minimum_required(VERSION 3.10)

project(LiveStreamSystem VERSION 1.0)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(tests)

# Find required packages
find_package(LibEvent REQUIRED)
find_package(FFmpeg REQUIRED)
find_package(ZeroMQ REQUIRED)

# Add executable
add_executable(live_stream_system src/main.c)

# Link libraries
target_link_libraries(live_stream_system
    PRIVATE
    LibEvent::LibEvent
    FFmpeg::FFmpeg
    ZeroMQ::ZeroMQ
)