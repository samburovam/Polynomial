cmake_minimum_required(VERSION 2.8) 

set (CMAKE_CXX_STANDARD 11)
set(PROJECT_NAME Polynomial)
project(${PROJECT_NAME}) 


set(main main)
set(List List)
set(Polynomial Polynomial)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE) 
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release) 
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/List ${CMAKE_CURRENT_SOURCE_DIR}/Polynomial) 

add_subdirectory(main)
add_subdirectory(List)
add_subdirectory(Polynomial)
add_subdirectory(gtest)
add_subdirectory(test)