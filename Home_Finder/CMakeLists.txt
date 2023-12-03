cmake_minimum_required(VERSION 3.26)
project(Home_Finder)

set(CMAKE_CXX_STANDARD 17)

add_executable(Home_Finder main.cpp
        Tester.h)

include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Home_Finder sfml-system sfml-window sfml-graphics sfml-audio sfml-network)


