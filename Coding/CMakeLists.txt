cmake_minimum_required(VERSION 3.10)

if(WIN32)
    set(CMAKE_SYSTEM_VERSION "10.0.18362.0")
endif()

project(LVideoEditorMain)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(EXCLUDE_DIRS ".git")
set(CURRENT_DIR ${CMAKE_SOURCE_DIR})
file(GLOB ALL_ITEMS RELATIVE ${CURRENT_DIR} ${CURRENT_DIR}/*)
message(STATUS "ALL_ITEMS: ${ALL_ITEMS}")

add_subdirectory(LLibraryMoudle)
add_subdirectory(LTimeLineMoudle)
add_subdirectory(LVideoEditor)


#set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT LVideoEditor)