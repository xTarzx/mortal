set(SOURCES
    main.cpp
    pose.cpp
    psik.cpp
    serialize.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

set(EXTERNAL_DIR ${PROJECT_SOURCE_DIR}/external)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${EXTERNAL_DIR}/raylib/src
        ${EXTERNAL_DIR}/raygui/src
        ${EXTERNAL_DIR}/raygui/examples/custom_file_dialog
        ${EXTERNAL_DIR}/box2d/include
        ${EXTERNAL_DIR}/json/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib box2d)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

