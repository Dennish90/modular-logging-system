find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(logAnalyzer
    src/main.cpp
    src/mainWindow.cpp
    include/logAnalyzer/mainWindow.h
)

target_include_directories(logAnalyzer
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(logAnalyzer
    PRIVATE
        Qt6::Widgets
)