project(TestGame)
cmake_minimum_required(VERSION 3.16)

set(GameName TestGame)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GAME_ENGINE_DIR D:/code/cpp/gameEngine)

file(
    GLOB_RECURSE LOCAL_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/${GameName}/*.cpp
)

add_executable(${PROJECT_NAME} source/entrypoint.cpp ${LOCAL_SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${GAME_ENGINE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ./source/${GameName})
target_include_directories(${PROJECT_NAME} PRIVATE ${GAME_ENGINE_DIRR}/third_party/SDL2/x86_64-w64-mingw32/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${GAME_ENGINE_DIR}/third_party/box2d/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${GAME_ENGINE_DIR}/third_party/opengl/glew/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${GAME_ENGINE_DIR}/third_party/entt/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${GAME_ENGINE_DIR}/third_party)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GAME_ENGINE_DIR}/lib/libGameEngineLib.a) #一定要在最上面
target_link_libraries(${PROJECT_NAME} PRIVATE ${GAME_ENGINE_DIR}/lib/libbox2d.a)
target_link_libraries(${PROJECT_NAME} PRIVATE -lmingw32)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GAME_ENGINE_DIR}/lib/libSDL2.a)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GAME_ENGINE_DIR}/lib/libSDL2main.a)
# target_link_libraries(${PROJECT_NAME} PRIVATE -mwindows -Wl,--dynamicbase -Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid)
target_link_libraries(${PROJECT_NAME} PRIVATE -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GAME_ENGINE_DIR}/lib/libopengl32.a)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GAME_ENGINE_DIR}/lib/libglew32.dll.a)


# add_custom_target(
#     test_game_copy_target ALL
#     DEPENDS copy_assets
# )

# add_custom_command(
#     OUTPUT copy_assets
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#             ${CMAKE_SOURCE_DIR}/assets
#             ${CMAKE_CURRENT_BINARY_DIR}/assets
#     DEPENDS always_rebuild
# )

# add_custom_command(
#     OUTPUT always_rebuild
#     COMMAND cmake -E echo "copy files"
# )