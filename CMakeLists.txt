cmake_minimum_required(VERSION 3.14)
project(c2d_filtering)

# Add Eigen library.
set(CMAKE_PREFIX_PATH "C:/Program FIles (x86)/Eigen3")
find_package(Eigen3 3.4 REQUIRED NO_MODULE)

# Add source content.
add_library(src_library 
  src/ContinuousTransferFunction 
  src/TransferFunctionDiscretizer
  )
target_include_directories(src_library PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Create basic main executible and link source content to executible.
add_executable(main src/main.cpp)
target_link_libraries(main PUBLIC src_library Eigen3::Eigen)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Exable testing and create executable.
enable_testing()

add_executable(
  hello_test
  tests/hello_test.cpp
)
target_link_libraries(
  hello_test
  GTest::gtest_main
  src_library
  Eigen3::Eigen
)

include(GoogleTest)
gtest_discover_tests(hello_test)
