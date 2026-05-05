add_library(logger
  src/logger.cpp
)

target_include_directories(logger
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(logger
  PUBLIC
    cxx_std_20
)