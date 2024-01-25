project(GameEngine VERSION 0.1.0)
cmake_minimum_required(VERSION 3.16)

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
add_compile_definitions("GENGINE_STATIC_LIB")

file(GLOB_RECURSE SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Render/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Render/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Actor/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Actor/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Event/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Event/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Opengl/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Opengl/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Script/*.cpp
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

add_library(${PROJECT_NAME} STATIC ${SRC_FILES} ${THIRD_PARTY_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/box2d/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/opengl/glew/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL2/x86_64-w64-mingw32/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/entt/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib/libbox2d.a)
target_link_libraries(${PROJECT_NAME} PRIVATE -lmingw32)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib/libSDL2.a)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib/libSDL2main.a)
target_link_libraries(${PROJECT_NAME} PRIVATE -mwindows -Wl,--dynamicbase -Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib/libopengl32.a)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib/libglew32.dll.a)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(
    TARGETS GameEngine
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

add_custom_command(
    TARGET GameEngine POST_BUILD
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND echo "install GameEngine library"
    COMMAND ${CMAKE_COMMAND} --install .
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)