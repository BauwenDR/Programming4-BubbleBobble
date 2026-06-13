cmake_minimum_required(VERSION 3.26)
project(Minigin)

if(EMSCRIPTEN)
    message("Using Emscripten!")
endif()

if(EMSCRIPTEN)
    set(TARGET_NAME bubble-bobble_web)
    set(TARGET_PARAM )
else()
    set(TARGET_NAME bubble-bobble)
    set(TARGET_PARAM WIN32)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(Libraries.cmake)

include(Minigin/CMakeLists.txt)
include(Game/CMakeLists.txt)

# Hint VS to set our game as the default startup project
if(NOT EMSCRIPTEN)
    set_property(TARGET bubble-bobble PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
    set_property(GLOBAL PROPERTY VS_STARTUP_PROJECT bubble-bobble)
endif()
