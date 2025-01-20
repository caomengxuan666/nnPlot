cmake_minimum_required(VERSION 3.7)

project(nnPlot)

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 查找 pkg-config(可选,or vcpkg)
find_package(PkgConfig)

# 查找spdlog
find_package(spdlog CONFIG REQUIRED)

# 使用 pkg-config 查找 Cairo
pkg_check_modules(Cairo REQUIRED cairo)

include_directories(include)

add_subdirectory(src)
add_subdirectory(examples)