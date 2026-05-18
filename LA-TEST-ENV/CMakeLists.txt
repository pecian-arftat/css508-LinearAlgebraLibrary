cmake_minimum_required(VERSION 3.16)
project(LinearAlgebraProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

# Add library
add_library(VectorTransformation3D
    VectorTransformation3D.cpp
    VectorTransformation3D.h
)

# Precompiled headers (optional)
target_precompile_headers(VectorTransformation3D PRIVATE pch.h)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# Test executable
add_executable(VectorTransformation3DTests
    test.cpp
)

target_link_libraries(VectorTransformation3DTests
    VectorTransformation3D
    GTest::gtest_main
)

# Register tests
include(GoogleTest)
gtest_discover_tests(VectorTransformation3DTests)