cmake_minimum_required(VERSION 3.5.0)
project(28_2_station VERSION 0.1.0 LANGUAGES C CXX)


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(28_2_station main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
