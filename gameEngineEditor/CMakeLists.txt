project(GameEngineEditor)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_WIN32_EXECUTABLE TRUE)

file(GLOB_RECURSE EDITOR_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)
# 為了moc，必須參與編譯
file(GLOB_RECURSE EDITOR_HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*/*.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*/*/*.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*/*/*.hpp
)

file(GLOB_RECURSE IMGUI
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/imgui/include/*.h
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/imgui/include/*.cpp
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/ImGuizmo/ImGuizmo.h
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/ImGuizmo/ImGuizmo.cpp
)

add_executable(${PROJECT_NAME} 
    editorEntryPoint.cpp 
    ${EDITOR_HEADER_FILES}
    ${EDITOR_SRC_FILES}
    ${THIRD_PARTY_SRC}
    ${IMGUI}
)

target_include_directories(${PROJECT_NAME} PRIVATE .)
target_include_directories(${PROJECT_NAME} PRIVATE ./include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/GameEngine/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/GameEngine/third_party/box2d/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/GameEngine/third_party/opengl/glew/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/GameEngine/third_party/SDL2/x86_64-w64-mingw32/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/GameEngine/third_party/entt/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/GameEngine/third_party)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/GameEngine/third_party/imgui/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/GameEngine/third_party/ImGuizmo)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/GameEngine/third_party/SDL2/x86_64-w64-mingw32/include/SDL2)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/lib/libGameEngine.a)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/libbox2d.a)
target_link_libraries(${PROJECT_NAME} PRIVATE -lmingw32)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/libSDL2.a)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/libSDL2main.a)
target_link_libraries(${PROJECT_NAME} PRIVATE -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -ldwmapi -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/libopengl32.a)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/libglew32.dll.a)

# WIN32_EXECUTABLE 會使console消失
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE OFF
        MACOSX_BUNDLE ON
    )
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
    )
endif ()