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

if( BUILD_TESTING )
  add_subdirectory( ${CMAKE_CURRENT_LIST_DIR}/tests )
endif()
