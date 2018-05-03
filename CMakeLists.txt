cmake_minimum_required(VERSION 2.6)

project(gpsConverterSimple)
add_definitions(-std=c++11)
add_definitions(-g)

include_directories(./include)

add_executable(gpsConverterTest
	src/gpsConverterTest.cpp
	)
	
#target_link_libraries(gpsConverterTest)
