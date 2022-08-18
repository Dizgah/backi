cmake_minimum_required(VERSION 3.5)

project(backi-core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MINGW)
    link_libraries(stdc++fs)

elseif (MSVC)

endif()

add_executable(backi-core main.cpp)
