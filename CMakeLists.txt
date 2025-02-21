cmake_minimum_required(VERSION 3.10)

project(tape_task LANGUAGES CXX)

add_executable(${PROJECT_NAME})

include(${CMAKE_CURRENT_LIST_DIR}/tape_task.cmake)

target_sources(${PROJECT_NAME}
    PRIVATE
    ${TAPE_TASK_SOURCES}
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${TAPE_TASK_INCLUDES}
)

target_compile_features(${PROJECT_NAME}
    PRIVATE
    cxx_std_20
)

find_package(yaml-cpp REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp)

if(BUILD_TESTING)
    find_package(GTest REQUIRED)
    find_package(yaml-cpp REQUIRED)

    add_executable(test_${PROJECT_NAME})

    include(${CMAKE_CURRENT_LIST_DIR}/tests/tests.cmake)

    target_sources(test_${PROJECT_NAME}
        PRIVATE
        ${TAPE_TASK_SOURCES}
        ${TAPE_TASK_TESTS_SOURCES}
    )

    target_include_directories(test_${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include/
        ${CMAKE_CURRENT_LIST_DIR}/tests/include
    )
    target_compile_features(test_${PROJECT_NAME} PRIVATE cxx_std_20)

    target_link_libraries(test_${PROJECT_NAME} PRIVATE
        yaml-cpp
        GTest::GTest
        GTest::Main
        -lgtest
        -lpthread)
endif()
