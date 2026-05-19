find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(logAnalyzer
    src/main.cpp
    src/mainWindow.cpp
    include/logAnalyzer/mainWindow.h
    ui/mainWindow.ui
)

set_property(TARGET logAnalyzer PROPERTY AUTOUIC_SEARCH_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
)

target_include_directories(logAnalyzer
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(logAnalyzer
    PRIVATE
        Qt6::Widgets
)