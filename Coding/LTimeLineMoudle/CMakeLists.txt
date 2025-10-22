cmake_minimum_required(VERSION 3.10)
project(LTimeLineMoudle)

set(CMAKE_CXX_STANDARD 11)

if(MSVC)
    add_compile_options(/Zc:__cplusplus)
    add_compile_options(/utf-8)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

add_library(${PROJECT_NAME} SHARED
    ltimelineexport.h
    ltimelinewidget.h
    ltimelinewidget.cpp
    ltimelineruler.h
    ltimelineruler.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
)

target_compile_definitions(${PROJECT_NAME} PRIVATE 
    LTIMELINEMOUDLE_DLL
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "LTimeLineMoudle"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)