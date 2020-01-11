cmake_minimum_required(VERSION 3.15)
project(jalebi VERSION 1.22.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost REQUIRED)
find_package(ArrayFire REQUIRED)

message("CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR}")
add_executable(jalebi src/main.cpp)
include_directories(PUBLIC include include/third_party /usr/local/include)
target_link_libraries(jalebi ArrayFire::af)