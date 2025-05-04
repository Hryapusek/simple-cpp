cmake_minimum_required(VERSION 3.18)
project(dependency)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(STANDALONE_NAME ${PROJECT_NAME}-standalone)

add_executable(${STANDALONE_NAME})

add_subdirectory(dependency_dir)

target_sources(${STANDALONE_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)
# cmake -S .. -B build -DCMAKE_SHARED_LIBS=OFF
target_link_libraries(${STANDALONE_NAME}
  PRIVATE
    dependency
)
