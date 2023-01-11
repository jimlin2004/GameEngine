cmake_minimum_required(VERSION 3.0.0)
project(GameEngine VERSION 0.1.0)

find_package(SDL2 REQUIRED)
link_libraries(SDL2)

find_package(SDL2_image REQUIRED)

find_package(OpenGL REQUIRED)
message(STATUS ${OPENGL_INCLUDE_DIR})
message(STATUS ${OPENGL_LIBRARIES})

find_package(glm REQUIRED)

find_package(GLEW REQUIRED)


file(GLOB_RECURSE SRC_FILE 
    src/*.cpp
    include/*.cpp
    src/*.c)
file(GLOB_RECURSE HEADER_FILES
    include/*.h
    include/*.hpp)
file(GLOB_RECURSE TEST_FILE
    test/*cpp
    test/*.h)
add_executable(${PROJECT_NAME} main.cpp ${SRC_FILE} ${TEST_FILE})
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
target_link_libraries(${PROJECT_NAME} SDL2_Image)
target_link_libraries(${PROJECT_NAME} GLEW::GLEW)
# target_link_libraries(${PROJECT_NAME} glm::glm)
target_link_libraries(${PROJECT_NAME} ${GLM_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
