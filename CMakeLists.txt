cmake_minimum_required(VERSION 3.18)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER "F:/devkitpro/devkitARM/bin/arm-none-eabi-gcc.exe")
set(CMAKE_CXX_COMPILER "F:/devkitpro/devkitARM/bin/arm-none-eabi-g++.exe")
set(CMAKE_TOOLCHAIN_FILE "F:/GBA-Toolchain/cmake/gba.toolchain.cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(GBAEngine LANGUAGES CXX)

include_directories(F:/devkitpro/devkitARM/arm-none-eabi/include
  F:/devkitpro/libgba/include
  F:/devkitPro/devkitARM/arm-none-eabi/include/c++/14.1.0)

# All project dependencies go here
# gba-toolchain sets `CMAKE_SYSTEM_NAME` to `AdvancedGameBoy`
if(CMAKE_SYSTEM_NAME STREQUAL AdvancedGameBoy)
    find_package(librom REQUIRED) # ROM runtime
    find_package(tonclib REQUIRED) # C development library
    find_package(libgba REQUIRED)
    find_package(agbabi REQUIRED) # Optimized library functions

endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/Engine)
add_subdirectory(${PROJECT_SOURCE_DIR}/Tests/Test_Core)
add_subdirectory(${PROJECT_SOURCE_DIR}/Tests/ECS_Test)
