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

include(Libraries.cmake)

include(Minigin/CMakeLists.txt)
include(Game/CMakeLists.txt)