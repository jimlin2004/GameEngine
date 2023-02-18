project(TestGame)
cmake_minimum_required(VERSION 3.16)
file(
    GLOB_RECURSE LOCAL_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(${PROJECT_NAME} entrypoint.cpp ${LOCAL_SRC_FILES} ${SRC_FILES} ${THIRD_PARTY_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE .)
target_link_libraries(${PROJECT_NAME} mingw32 SDL2main SDL2)
target_link_libraries(${PROJECT_NAME} GLEW::GLEW)

add_custom_target(
    test_game_copy_target ALL
    DEPENDS copy_assets
)

add_custom_command(
    OUTPUT copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            ${CMAKE_CURRENT_BINARY_DIR}/assets
    DEPENDS always_rebuild
)

add_custom_command(
    OUTPUT always_rebuild
    COMMAND cmake -E echo "copy files"
)