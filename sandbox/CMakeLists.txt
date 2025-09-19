# Standalone sandbox executeable
add_executable(sandbox EXCLUDE_FROM_ALL main.cpp)

# Link the main library target to allow component testing
target_link_libraries(sandbox PRIVATE cpps)

# Set C++ standard
target_compile_features(sandbox PRIVATE cxx_std_20)