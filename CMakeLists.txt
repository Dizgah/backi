cmake_minimum_required(VERSION 3.5)

project(backi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(backi main.cpp)

install(TARGETS backi
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
