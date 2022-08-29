cmake_minimum_required(VERSION 3.5)

project(backi-core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (PROJECT_DIR ./)

if( WIN32)

    if(MINGW)
        
        link_libraries(stdc++fs)

    elseif (MSVC)

    endif()

elseif( UNIX AND NOT APPLE)

    link_libraries(stdc++fs)
    set (PROJECT_LINK_LIBS)

endif()

find_package (Threads)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)

find_package(Boost COMPONENTS filesystem thread REQUIRED)
if(Boost_FOUND)

    include_directories(${Boost_INCLUDE_DIRS} ${PROJECT_DIR}/inc)
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS} ${PROJECT_DIR}/lib)

 else()
    message(STATUS "BOOST Not Found!!!")

endif()

#compile all *.cpp source files under src folder
file (GLOB SOURCES "${PROJECT_DIR}/*.cpp" "${PROJECT_DIR}/src/*.cpp")

add_executable(backi-core main.cpp ${SOURCES})
target_link_libraries(backi-core ${PROJECT_LINK_LIBS} ${Boost_SYSTEM_LIBRARY} Threads::Threads)
