cmake_minimum_required(VERSION 3.18)
project(dependency)

add_library(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
  PRIVATE # Not public because we don't want other projects to use it. They simply dont need it.
    ${CMAKE_CURRENT_SOURCE_DIR}/src

  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(${PROJECT_NAME}
  PRIVATE # Not public because what sense it makes to be public?
    ${CMAKE_CURRENT_SOURCE_DIR}/src/${PROJECT_NAME}/dependency.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/${PROJECT_NAME}/impl.cc
)
