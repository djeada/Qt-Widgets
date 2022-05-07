cmake_minimum_required(VERSION 3.14)

project(custom_type LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_executable(${PROJECT_NAME}
  main.cpp
  custom_type.h
  custom_type.cpp
)
target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Core)
