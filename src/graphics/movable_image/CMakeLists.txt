cmake_minimum_required(VERSION 3.14)

project(Movable_Image LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Widgets Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets Gui REQUIRED)

set(project_headers
  main_window.h
  movable_image.h
)

set(project_sources
  main.cpp
  main_window.cpp
  movable_image.cpp
)

add_executable(${PROJECT_NAME} ${project_headers} ${project_sources})

target_link_libraries(${PROJECT_NAME}  Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets)
