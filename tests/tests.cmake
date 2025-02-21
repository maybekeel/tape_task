list(APPEND TAPE_TASK_TESTS_INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}/tests/include
)
list(APPEND TAPE_TASK_TESTS_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/config_test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/file_tape_test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/file_tape_creator_test.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/sorter_test.cpp
)