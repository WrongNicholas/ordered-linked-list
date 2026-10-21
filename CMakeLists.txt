
cmake_minimum_required(VERSION 3.14)
project(cpp_toolkit LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# library target
add_library(ordered_linked_list INTERFACE)
target_include_directories(ordered_linked_list INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(app_new src/main.cpp)
add_executable(app_old src/main_old.cpp)

target_link_libraries(app_new PRIVATE ordered_linked_list)
target_link_libraries(app_old PRIVATE ordered_linked_list)

enable_testing()
add_subdirectory(tests)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
endif()
