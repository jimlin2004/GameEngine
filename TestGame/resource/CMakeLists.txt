project(TestGameLib)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GAME_ENGINE_DIR D:/code/cpp/gameEngine/GameEngine)
add_compile_definitions("GENGINE_DLL")

file(
    GLOB_RECURSE LOCAL_SRC_FILES
    ${CMAKE_SOURCE_DIR}/source/${GameName}/*.cpp
)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os -Wall -s")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_FLAGS_RELEASE} -Os -Wall -s")
endif ()

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
target_include_directories(${PROJECT_NAME} PUBLIC ${GAME_ENGINE_DIR}/third_party/entt/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${GAME_ENGINE_DIR}/third_party)
target_link_libraries(${PROJECT_NAME} PUBLIC ${GAME_ENGINE_DIR}/lib/libGameEngine.a) #一定要在最上面