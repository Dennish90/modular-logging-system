cmake_minimum_required(VERSION 3.20)

project(ModularLoggingSystem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(logger)
add_subdirectory(demoApp)
add_subdirectory(logAnalyzer)
add_subdirectory(tests)