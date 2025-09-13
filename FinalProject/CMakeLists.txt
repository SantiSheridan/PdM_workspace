cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME FinalProject)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here

    # Lib/api_debug
    ${CMAKE_SOURCE_DIR}/lib/api_debug/fw/src/api.c
    ${CMAKE_SOURCE_DIR}/lib/api_debug/fw/src/api_call.c
    ${CMAKE_SOURCE_DIR}/lib/api_debug/fw/src/api_functions.c
    ${CMAKE_SOURCE_DIR}/lib/api_debug/fw/src/api_utils.c

    #Lib/mcu_446re
    ${CMAKE_SOURCE_DIR}/lib/mcu_446re/fw/src/dev_uart.c
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths

    #Lib/api_debug
    ${CMAKE_SOURCE_DIR}/lib/api_debug/fw/src
    ${CMAKE_SOURCE_DIR}/lib/api_debug/fw/inc

    #Lib/mcu_446re
    ${CMAKE_SOURCE_DIR}/lib/mcu_446re/fw/src
    ${CMAKE_SOURCE_DIR}/lib/mcu_446re/fw/inc
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
