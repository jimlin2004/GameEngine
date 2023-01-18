cmake_minimum_required(VERSION 3.0.0)
project(GameEngine VERSION 0.1.0)

find_package(SDL2 REQUIRED)
link_libraries(SDL2)

find_package(OpenGL REQUIRED)
message(STATUS ${OPENGL_INCLUDE_DIR})
message(STATUS ${OPENGL_LIBRARIES})

find_package(GLEW REQUIRED)


file(GLOB_RECURSE SRC_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/*.cpp
    )
file(GLOB_RECURSE HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/*.hpp)
file(GLOB_RECURSE TEST_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/test/*cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test/*.h)
add_executable(${PROJECT_NAME} main.cpp ${SRC_FILE} ${TEST_FILE})
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
target_link_libraries(${PROJECT_NAME} GLEW::GLEW)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thrid_party)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
