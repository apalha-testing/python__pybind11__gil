cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(interpolate VERSION 0.1.0)

find_package(OpenMP)

# Include dir
include_directories(/usr/local/include)

# Src
AUX_SOURCE_DIRECTORY(src SRC_FILES)

# Headers
set(PROJECT_SOURCE_DIR "src")
set(PROJECT_INCLUDE_DIR "include/interpolate_bits")

# Source files
set(SOURCE_FILES
    ${PROJECT_INCLUDE_DIR}/interpolate.hpp
    ${PROJECT_SOURCE_DIR}/interpolate.cpp
)

# Set up such that XCode organizes the files correctly
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})

# Add library
add_library(interpolate SHARED ${SOURCE_FILES})

target_link_libraries(interpolate PUBLIC OpenMP::OpenMP_CXX)

# Include directories
target_include_directories(interpolate PRIVATE include/interpolate_bits)

# Install
install(TARGETS interpolate DESTINATION lib)

# Install the headers
install(FILES include/interpolate DESTINATION include)

# Create base directory
install(DIRECTORY include/interpolate_bits DESTINATION include)
