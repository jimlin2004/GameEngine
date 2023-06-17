cmake_minimum_required(VERSION 3.16)
project(GameEngine VERSION 0.1.0)

include(${CMAKE_CURRENT_SOURCE_DIR}/third_party/SDL2/x86_64-w64-mingw32/lib/cmake/SDL2/sdl2-config.cmake)
message(STATUS ${SDL2_INCLUDE_DIR})
message(STATUS ${SDL2_LIBRARIES})

find_package(GLEW REQUIRED)
message(STATUS ${GLEW_INCLUDE_DIR})
message(STATUS ${GLEW_LIBRARIES})

set(GLEW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/opengl/glew/include)
set(GLEW_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/third_party/opengl/glew/lib/libglew32.dll.a)

message(STATUS ${GLEW_INCLUDE_DIR})
message(STATUS ${GLEW_LIBRARIES})

file(GLOB_RECURSE SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(GLOB_RECURSE THIRD_PARTY_SRC
    # ${CMAKE_CURRENT_SOURCE_DIR}/third_party/box2d/src/*.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/third_party/box2d/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/stb_image/*.cpp
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

# link_libraries(mingw32 SDL2main SDL2)
# link_libraries(GLEW::GLEW)

# add_subdirectory(./snake)
add_subdirectory(./test)
add_subdirectory(./gameEngineEditor)

add_executable(${PROJECT_NAME} main.cpp ${SRC_FILES} ${THIRD_PARTY_SRC})

# target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} mingw32 SDL2main SDL2)
target_link_libraries(${PROJECT_NAME} GLEW::GLEW)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
