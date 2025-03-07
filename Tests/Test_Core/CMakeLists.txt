include_directories(src/)
add_library(TestCore STATIC
        src/test_core.cpp
        include/test_core.h)

install(TARGETS Engine LIBRARY DESTINATION out/Tests_Core
        DESTINATION out/Tests_Core
        PUBLIC_HEADER DESTINATION ${CMAKE_SOURCE_DIR}/out/Test_Core/include/test_core.h)
