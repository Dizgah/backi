cmake_minimum_required(VERSION 3.5)

project(backi-core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MINGW)
    link_libraries(stdc++fs)

elseif (MSVC)

endif()


set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)

find_package(Boost COMPONENTS filesystem thread REQUIRED)
if(Boost_FOUND)

    include_directories(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

 else()
    message(STATUS "BOOST Not Found!!!")

endif()

add_executable(backi-core main.cpp)
target_link_libraries(backi-core ${Boost_SYSTEM_LIBRARY})