list(APPEND TAPE_TASK_INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}/include
)

list(APPEND TAPE_TASK_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/config.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/file_tape.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/sorter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/file_tape_creator.cpp
)
