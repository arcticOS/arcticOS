cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(arcticOS_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

file(GLOB_RECURSE arcticOS_SOURCE CONFIGURE_DEPENDS
    "source/*.c"
)

add_executable(arcticOS ${INCLUDE_DIRECTORIES} ${arcticOS_SOURCE})

IF (NOT DEFINED _MODEL)
    SET(_MODEL EVT4)
ENDIF()
ADD_DEFINITIONS(-D${_MODEL}=1)

include_directories(include/)
include_directories(include/strings)
include_directories(include/hardware/evt4)
include_directories(include/hardware/ili9341)

target_link_libraries(arcticOS pico_stdlib hardware_spi)

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

pico_enable_stdio_usb(arcticOS 1)
pico_enable_stdio_uart(arcticOS 1)

pico_add_extra_outputs(arcticOS)