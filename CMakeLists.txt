cmake_minimum_required(VERSION 3.10)
project(SYNTH)

set(CMAKE_C_STANDARD 99)

enable_testing()

# Add source and include directories
include_directories(${CMAKE_SOURCE_DIR}/inc)
file(GLOB_RECURSE LIB_SOURCES "src/*.c")
list(FILTER LIB_SOURCES EXCLUDE REGEX ".*main.c$")

# Add the synthesizer library (used by both the main program and tests)
add_library(synth_lib ${LIB_SOURCES})

# Add the main program executable
add_executable(synth src/main.c)
target_link_libraries(synth synth_lib asound m) # Link ALSA and math library

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add FFF
add_subdirectory(unit_tests/lib/fff)

# Add test files
file(GLOB TEST_SOURCES "unit_tests/*.cpp")

# Add the test executable
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests ${GTEST_LIBRARIES} pthread synth_lib gtest_main)

# Ensure FFF is included
target_include_directories(tests PRIVATE unit_tests/lib/fff)

# Make sure sources can be included in tests
target_include_directories(tests PRIVATE src)

# Define the UNIT_TEST macro for tests
target_compile_definitions(tests PRIVATE UNIT_TEST)

add_test(NAME tests COMMAND tests)