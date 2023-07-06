cmake_minimum_required(VERSION 3.16)
project(GameEngine VERSION 0.1.0)

file(GLOB_RECURSE SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(GLOB_RECURSE THIRD_PARTY_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/stb_image/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/json/json.hpp
)

file(GLOB_RECURSE HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/*.hpp
)

file(GLOB_RECURSE DEBUG_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/debug/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/debug/*.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/box2d/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/opengl/glew/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL2/x86_64-w64-mingw32/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/entt/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party)



add_executable(${PROJECT_NAME} main.cpp ${SRC_FILES} ${THIRD_PARTY_SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib/libbox2d.a)
target_link_libraries(${PROJECT_NAME} PRIVATE -lmingw32)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib/libSDL2.a)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib/libSDL2main.a)
target_link_libraries(${PROJECT_NAME} PRIVATE -mwindows -Wl,--dynamicbase -Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib/libopengl32.a)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib/libglew32.dll.a)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

project(GameEngineLib VERSION 0.1.0)
file(GLOB_RECURSE SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(GLOB_RECURSE THIRD_PARTY_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/stb_image/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/json/json.hpp
)

file(GLOB_RECURSE HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/*.hpp
)

file(GLOB_RECURSE DEBUG_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/debug/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/debug/*.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/box2d/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/opengl/glew/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL2/x86_64-w64-mingw32/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party/entt/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/third_party)

add_library(GameEngineLib STATIC ${SRC_FILES} ${THIRD_PARTY_SRC})

target_link_libraries(GameEngineLib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib/libbox2d.a)
target_link_libraries(GameEngineLib PRIVATE -lmingw32)
target_link_libraries(GameEngineLib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib/libSDL2.a)
target_link_libraries(GameEngineLib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib/libSDL2main.a)
target_link_libraries(GameEngineLib PRIVATE -mwindows -Wl,--dynamicbase -Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid)
target_link_libraries(GameEngineLib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib/libopengl32.a)
target_link_libraries(GameEngineLib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib/libglew32.dll.a)

target_include_directories(GameEngineLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(
    TARGETS GameEngineLib 
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

add_custom_command(
    TARGET GameEngineLib POST_BUILD
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target install
)

# add_subdirectory(./snake)
add_subdirectory(./TestGame)
add_subdirectory(./gameEngineEditor)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)