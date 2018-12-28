cmake_minimum_required(VERSION 3.6)
project(main)

#set(CMAKE_CXX_FLAGS14 "${CMAKE_CXX_FLAGS} -std=c++13")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(SOURCE_FILES main.cpp yourcode/submit-6MixQuery.cpp yourcode/submit-5MixQueryPolygon.cpp yourcode/submit-4MixQueryPoint.cpp yourcode/submit-3AddBeforeQuery.cpp yourcode/submit-2AddPointBeforeQueryPolygon.cpp yourcode/submit-1AddPolygonBeforeQueryPoint.cpp yourcode/header.cpp)
add_executable(main ${SOURCE_FILES})
