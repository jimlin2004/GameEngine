project(GameEngineEditor)
cmake_minimum_required(VERSION 3.16)

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -DNDEBUG")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -Wall -g")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Wall -g")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE EDITOR_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(${PROJECT_NAME} 
    editorEntryPoint.cpp 
    ${EDITOR_SRC_FILES}
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

target_link_libraries(${PROJECT_NAME} PRIVATE
    GameEngine
    ImGui
)

# WIN32_EXECUTABLE 會使console消失
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE OFF)