cmake_minimum_required(VERSION 3.10)
project(mortal VERSION 0.1.2)


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_subdirectory(external/raylib)
add_subdirectory(external/box2d)
add_subdirectory(src)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_custom_target(run
COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${PROJECT_NAME} 
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    DEPENDS ${EXECUTABLE_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Building and running ${EXECUTABLE_NAME}..."
    )
    
set (DATA_SRC ${PROJECT_SOURCE_DIR}/data)
set (DATA_DEST ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data)
add_custom_target(sync_data ALL
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${DATA_DEST}
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${DATA_SRC} ${DATA_DEST}
  COMMENT "Copying data from ${PROJECT_SOURCE_DIR}/data to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data"
)