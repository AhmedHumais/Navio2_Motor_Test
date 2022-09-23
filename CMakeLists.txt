cmake_minimum_required(VERSION 2.8.10)

project(motor_test)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

include_directories(
    include
)

file(GLOB_RECURSE SRCs src/*.cpp)

list(REMOVE_ITEM SRCs "src/main.cpp")

add_library(${PROJECT_NAME} ${SRCs})

add_executable(motor_run src/main.cpp)

target_link_libraries(motor_run ${PROJECT_NAME})
