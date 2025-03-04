cmake_minimum_required( VERSION 3.22 )
project( test_tape_task LANGUAGES CXX )

find_package(GTest REQUIRED)
find_package(yaml-cpp REQUIRED)

include(${CMAKE_CURRENT_LIST_DIR}/tests.cmake)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
    ${TAPE_TASK_SOURCES}
    ${TAPE_TASK_TESTS_SOURCES}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../include/
    ${CMAKE_CURRENT_LIST_DIR}/include
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_link_libraries(${PROJECT_NAME} PRIVATE
    yaml-cpp
    GTest::GTest
    GTest::Main
    -lgtest
    -lpthread)

if(NOT ${CMAKE_CURRENT_BINARY_DIR} EQUAL ${CMAKE_BINARY_DIR} )
  add_custom_command( TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND
    ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
    ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
)
endif()
