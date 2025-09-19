cmake_minimum_required(VERSION 3.16)
include(FetchContent)

# --- Download GoogleTest ---
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# --- Enable testing ---
enable_testing()
include(GoogleTest)

# --- Helper function to add all tests in a module (recursive) ---
function(add_module_tests MODULE_DIR MODULE_NAME)
    # Collect all .cpp files recursively
    file(GLOB_RECURSE MODULE_SOURCES
        "${MODULE_DIR}_Tests/*.cpp"
        "${MODULE_DIR}_Tests/*/*.cpp"
    )

    if(NOT MODULE_SOURCES)
        message(WARNING "No source files found for module ${MODULE_NAME} in ${MODULE_DIR}")
        return()
    endif()

    # Define executable for this module
    add_executable(${MODULE_NAME}_tests ${MODULE_SOURCES})

    # Link cpps and GoogleTest
    target_link_libraries(${MODULE_NAME}_tests
        PRIVATE
            cpps
            GTest::gtest
            GTest::gtest_main
    )

    # Set C++ standard to 20
    target_compile_features(${MODULE_NAME}_tests PRIVATE cxx_std_20)

    # Register tests with CTest
    gtest_discover_tests(${MODULE_NAME}_tests)
endfunction()

# --- Add your modules ---
# Pass paths without quotes
add_module_tests(${CMAKE_CURRENT_SOURCE_DIR}/Array Array)
add_module_tests(${CMAKE_CURRENT_SOURCE_DIR}/Nullable Nullable)
add_module_tests(${CMAKE_CURRENT_SOURCE_DIR}/String String)
add_module_tests(${CMAKE_CURRENT_SOURCE_DIR}/Tuple Tuple)
add_module_tests(${CMAKE_CURRENT_SOURCE_DIR}/ListTypes ListTypes)
add_module_tests(${CMAKE_CURRENT_SOURCE_DIR}/QueueTypes QueueTypes)

# --- For optional top-level aggregator executable ---
file(GLOB_RECURSE ALL_TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*/*/*.cpp"
)

if(ALL_TEST_SOURCES)
    add_executable(all_tests ${ALL_TEST_SOURCES})
    target_link_libraries(all_tests PRIVATE cpps GTest::gtest GTest::gtest_main)
    target_compile_features(all_tests PRIVATE cxx_std_20)
    gtest_discover_tests(all_tests)
endif()
