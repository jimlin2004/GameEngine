cmake_minimum_required(VERSION 3.16)
project(GameLauncher)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE GAME_LAUNCHER_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

add_executable(GameLauncher
    ${CMAKE_CURRENT_SOURCE_DIR}/entryPoint.cpp 
    ${GAME_LAUNCHER_SRC_FILES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    .
    ./include
    ${CMAKE_SOURCE_DIR}/GameEngine/include
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/box2d/include
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/opengl/glew/include
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/SDL2/x86_64-w64-mingw32/include
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/entt/include
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/imgui/include
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/ImGuizmo/include
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/SDL2/x86_64-w64-mingw32/include/SDL2
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lua/include
)

target_link_libraries(GameLauncher PRIVATE 
    GameEngine
)

# WIN32_EXECUTABLE 會使console消失
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE OFF)