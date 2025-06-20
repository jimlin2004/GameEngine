cmake_minimum_required(VERSION 3.16)
project(GameEngine VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Debug/Release flags
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -Wall -g")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Wall -g")

add_compile_definitions(GENGINE_STATIC_LIB)

# === 收集檔案 ===
file(GLOB_RECURSE SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.[ch]pp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.[ch]
)

file(GLOB_RECURSE THIRD_PARTY_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/stb_image/*.cpp
)

set(LUA_LIB
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/sol/config.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/sol/forward.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/sol/sol.hpp
)

add_library(${PROJECT_NAME} STATIC
    ${SRC_FILES}
    ${THIRD_PARTY_SRC}
    ${LUA_LIB}
)

# === Include paths ===
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/box2d/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/opengl/glew/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL2/x86_64-w64-mingw32/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL2/x86_64-w64-mingw32/include/SDL2
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/entt/include
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua/include
)


target_link_libraries(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/libbox2d.a
    -lmingw32
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/libSDL2.a
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/libSDL2main.a
    -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -ldwmapi -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/libopengl32.a
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/libglew32.dll.a
    ${CMAKE_SOURCE_DIR}/GameEngine/third_party/lib/liblua.a
)


# === CPack 設定 ===
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)