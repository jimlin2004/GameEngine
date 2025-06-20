cmake_minimum_required(VERSION 3.16)
project(ImGui)
set(CMAKE_CXX_STANDARD 17)

# ---------- ImGui source ----------
file(GLOB IMGUI_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/include/*.cpp
)

# ---------- ImGuizmo ----------
set(IMGUIZMO_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/ImGuizmo/ImGuizmo.cpp
)

add_library(${PROJECT_NAME} STATIC
    ${IMGUI_SOURCES}
    ${IMGUIZMO_SRC}
)

# ---------- Include paths ----------
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ImGuizmo
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/SDL2/x86_64-w64-mingw32/include
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/SDL2/x86_64-w64-mingw32/include/SDL2
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/opengl/glew/include
)

# ---------- Libraries ----------
target_link_libraries(${PROJECT_NAME} PRIVATE
    -lmingw32
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/libSDL2.a
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/libSDL2main.a
    -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -ldwmapi -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/libopengl32.a
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/libglew32.dll.a
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/liblua.a
)