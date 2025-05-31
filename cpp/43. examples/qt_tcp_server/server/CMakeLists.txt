cmake_minimum_required(VERSION 3.15)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_BUILD_RPATH "./libs")

include_guard(GLOBAL)

project(gui-dosimeter
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

if("${CMAKE_GENERATOR}" MATCHES "^Visual Studio")
  set(CMAKE_GENERATOR_PLATFORM "x64" CACHE STRING "" FORCE)
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if("${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Linux" AND MINGW AND NOT CYGWIN)
  message(STATUS "[${PROJECT_FULL_NAME}] Mingw on linux detected. Statically linking universal C runtime library")

  foreach(LANG C CXX)
    set(CMAKE_${LANG}_STANDARD_LIBRARIES "${CMAKE_${LANG}_STANDARD_LIBRARIES} -lucrt")
    message(STATUS "CMAKE_${LANG}_STANDARD_LIBRARIES: ${CMAKE_${LANG}_STANDARD_LIBRARIES}")
  endforeach()
endif()

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick QuickControls2 Widgets Qml Gui)
find_package(dosimeter-server REQUIRED)

add_executable(${PROJECT_NAME})
add_executable(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/c++
)

target_sources(${PROJECT_NAME}
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/qml/qml.qrc
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
  dosimeter-server::dosimeter-server-library
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND}
  -D SEARCH_DIR=${CMAKE_BINARY_DIR}
  -D OUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR}
  -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/copy_dlls.cmake
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND}
  -D SEARCH_DIR=${CMAKE_BINARY_DIR}
  -D OUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR}
  -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/copy_so.cmake
)
