project(Snake)
cmake_minimum_required(VERSION 3.0.0)
file(
    GLOB_RECURSE LOCAL_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(${PROJECT_NAME} main.cpp ${LOCAL_SRC_FILES} ${SRC_FILES} ${THIRD_PARTY_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE .)