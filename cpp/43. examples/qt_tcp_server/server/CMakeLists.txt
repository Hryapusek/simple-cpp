cmake_minimum_required(VERSION 3.15)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_BUILD_RPATH "./libs")

include_guard(GLOBAL)

project(example-qt-tcp-server
  VERSION 0.0.1
  LANGUAGES CXX
)

option(${PROJECT_NAME}_STANDALONE "Build standalone executable" ON)

if(NOT CMAKE_CXX_STANDARD)
  message(STATUS "[${PROJECT_NAME}] setting c++ standard to c++14")
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick QuickControls2 Widgets Qml Gui)

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++
)

target_sources(${PROJECT_NAME}
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/${PROJECT_NAME}/server/server.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++/${PROJECT_NAME}/main.cc
  
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Quick
  Qt${QT_VERSION_MAJOR}::QuickControls2
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Qml
  Qt${QT_VERSION_MAJOR}::Gui
)
