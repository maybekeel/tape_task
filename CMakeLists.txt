cmake_minimum_required(VERSION 3.10)

project(type_task LANGUAGES CXX)

add_executable( ${PROJECT_NAME} )

target_sources( ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/config.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/file_tape.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/tape_sort.cpp
)

target_include_directories( ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_compile_features( ${PROJECT_NAME}
    PRIVATE
    cxx_std_20
)

find_package(yaml-cpp REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp)

