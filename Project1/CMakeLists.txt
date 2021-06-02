cmake_minimum_required(VERSION 3.10)
project(progtestCmake)

set(CMAKE_CXX_STANDARD 17)


SET(GCC_COVERAGE_COMPILE_FLAGS " -Wall -pedantic")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")


include_directories(.)
add_executable(progtestCmake
        common.h
        progtest_solver.h
        sample_tester.cpp
        sample_tester.h
        solution.cpp)

target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/x86_64-linux-gnu/libprogtest_solver.a)