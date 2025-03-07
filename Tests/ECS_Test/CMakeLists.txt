include_directories(src/)
add_executable(ECS_Test
        src/main.cpp
        src/ComponentDefinitions.cpp)

target_include_directories(ECS_Test PUBLIC 
  ${CMAKE_SOURCE_DIR}/Engine/include 
  ${CMAKE_SOURCE_DIR}/Engine/include/ECS
  ${CMAKE_SOURCE_DIR}/Tests/Test_Core/include)

# gba-toolchain sets `CMAKE_SYSTEM_NAME` to `AdvancedGameBoy`
if(CMAKE_SYSTEM_NAME STREQUAL AdvancedGameBoy)
    target_compile_options(ECS_Test PRIVATE -mthumb -fomit-frame-pointer)
    target_link_libraries(ECS_Test PRIVATE librom libgba agbabi tonclib Engine)
    
    # ROM header info
    set_target_properties(ECS_Test PROPERTIES
        ROM_TITLE "My Game"
        ROM_ID AABE
        ROM_MAKER CD
        ROM_VERSION 1
    )

    # install to .gba
    install_rom(ECS_Test DESTINATION out/ECS_Test)
endif()
