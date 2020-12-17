cmake_minimum_required(VERSION 3.10)
project(aeda1516_ci4)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)



add_executable(aeda1516_ci4 main.cpp Tests/tests.cpp Tests/Cinema.cpp Tests/CinemaFinder.cpp Tests/Film.cpp Tests/FilmTime.cpp)

target_link_libraries(aeda1516_ci4 gtest gtest_main)
