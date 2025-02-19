cmake_minimum_required(VERSION 3.10)

project(tape_task LANGUAGES CXX)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/config.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/file_tape.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/tape_sort.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/file_tape_create.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
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

    target_sources(test_${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/tests/config_test.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/config.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/file_tape.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/tape_sort.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/file_tape_create.cpp
    )

    target_include_directories(test_${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include/
        ${CMAKE_CURRENT_LIST_DIR}/tests/
    )
    target_compile_features(test_${PROJECT_NAME} PRIVATE cxx_std_20)

    target_link_libraries(test_${PROJECT_NAME} PRIVATE
        yaml-cpp
        GTest::GTest
        GTest::Main
        -lgtest
        -lpthread)
endif()
