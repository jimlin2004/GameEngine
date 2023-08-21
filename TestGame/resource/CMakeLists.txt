project(TestGameLib)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GAME_ENGINE_DIR D:/code/cpp/gameEngine/GameEngine)


file(
    GLOB_RECURSE LOCAL_SRC_FILES
    ${CMAKE_SOURCE_DIR}/source/${GameName}/*.cpp
    ${GAME_ENGINE_DIR}/src/Event/Input.cpp
    ${GAME_ENGINE_DIR}/src/Component/Component.cpp
    ${GAME_ENGINE_DIR}/src/Actor/Actor.cpp
    ${GAME_ENGINE_DIR}/src/Scene/Scene.cpp
)

add_library(${PROJECT_NAME} SHARED ${LOCAL_SRC_FILES})

# 取消dll的前綴"Lib" 
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
# 命名dll為GameEngineScript.dll
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "GameEngineScript")
# 輸出dll到build/lib
set_target_properties(${PROJECT_NAME} PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

target_include_directories(${PROJECT_NAME} PUBLIC ${GAME_ENGINE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/source/${GameName})
target_include_directories(${PROJECT_NAME} PUBLIC ${GAME_ENGINE_DIR}/third_party/SDL2/x86_64-w64-mingw32/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${GAME_ENGINE_DIR}/third_party/box2d/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${GAME_ENGINE_DIR}/third_party/opengl/glew/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${GAME_ENGINE_DIR}/third_party/entt/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${GAME_ENGINE_DIR}/third_party)
# target_link_libraries(${PROJECT_NAME} PUBLIC ${GAME_ENGINE_DIR}/lib/libGameEngine.a) #一定要在最上面
# target_link_libraries(${PROJECT_NAME} PUBLIC ${GAME_ENGINE_DIR}/lib/libbox2d.a)
# target_link_libraries(${PROJECT_NAME} PUBLIC -lmingw32)
# target_link_libraries(${PROJECT_NAME} PUBLIC ${GAME_ENGINE_DIR}/lib/libSDL2.a)
# target_link_libraries(${PROJECT_NAME} PUBLIC ${GAME_ENGINE_DIR}/lib/libSDL2main.a)
# target_link_libraries(${PROJECT_NAME} PUBLIC -mwindows -Wl,--dynamicbase -Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid)
# target_link_libraries(${PROJECT_NAME} PUBLIC -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid)
# target_link_libraries(${PROJECT_NAME} PUBLIC ${GAME_ENGINE_DIR}/lib/libopengl32.a)
# target_link_libraries(${PROJECT_NAME} PUBLIC ${GAME_ENGINE_DIR}/lib/libglew32.dll.a)

