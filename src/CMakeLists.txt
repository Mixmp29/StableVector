set(test_name Test)
set(vec_name Vector)

add_executable(
    ${test_name}
    vector/VectorTest.cpp
)

add_library(
  ${vec_name} INTERFACE
  vector/StableVector.hpp
)

include(CompileOptions)

set_compile_options(${test_name})

target_include_directories(
  ${vec_name}
  INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(
  ${test_name}
  PRIVATE
    Vector
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(${test_name})
