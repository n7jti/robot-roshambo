cmake_minimum_required(VERSION 3.22)

set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
set(PICO_SDK_IMPORT_FILE ${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

include(${PICO_SDK_IMPORT_FILE})

project(robot-roshambo C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include_directories(inc)
add_subdirectory(src)