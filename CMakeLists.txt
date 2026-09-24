cmake_minimum_required(VERSION 3.20)

project(ModularLoggingSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(logger)
add_subdirectory(demoApp)
add_subdirectory(logAnalyzer)