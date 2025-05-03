cmake_minimum_required(VERSION 3.18)
project(dependency)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(STANDALONE_NAME ${PROJECT_NAME}-standalone)

# Package has
# Инклюды
# Скомпилированная библиотека
# dependencyConfig.cmake для подключения

find_package(fmt REQUIRED)
# add_subdirectory()

add_executable(${STANDALONE_NAME})

target_sources(${STANDALONE_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_compile_definitions(${STANDALONE_NAME} 
  PRIVATE
    COMPILER_NAME_s0=${CMAKE_CXX_COMPILER_ID}
)

target_link_libraries(${STANDALONE_NAME}
  PRIVATE
    fmt::fmt
)
