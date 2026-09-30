include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

add_executable(ordered_linked_list_tests test_ordered_linked_list.cpp)
target_link_libraries(ordered_linked_list_tests
      PRIVATE
        ordered_linked_list
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ordered_linked_list_tests)
