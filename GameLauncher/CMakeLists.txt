project(GameLauncher)
cmake_minimum_required(VERSION 3.16)

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -DNDEBUG")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -Wall -g")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Wall -g")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_WIN32_EXECUTABLE TRUE)

# 編譯可改的參數

set(ExecutionFilename "GameLauncher")

file(GLOB_RECURSE GAME_LAUNCHER_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GameLauncher.cpp
)

file(GLOB_RECURSE GAME_LAUNCHER_HEADER_FILES
${CMAKE_CURRENT_SOURCE_DIR}/src/GameLauncher.h
)

add_executable(${ExecutionFilename}
    editorEntryPoint.cpp 
    ${GAME_LAUNCHER_SRC_FILES}
    ${GAME_LAUNCHER_HEADER_FILES}
    ${THIRD_PARTY_SRC}
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
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lua/include)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/lib/libGameEngine.a)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/libbox2d.a)
target_link_libraries(${PROJECT_NAME} PRIVATE -lmingw32)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/libSDL2.a)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/libSDL2main.a)
target_link_libraries(${PROJECT_NAME} PRIVATE -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -ldwmapi -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/libopengl32.a)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/libglew32.dll.a)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/liblua.a)

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