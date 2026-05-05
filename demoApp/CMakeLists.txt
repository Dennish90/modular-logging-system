add_executable(demoApp
  src/main.cpp
)

target_link_libraries(demoApp
  PRIVATE
    logger
)