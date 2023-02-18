project(GameEngineEditor)
cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_PREFIX_PATH D:/QT/6.4.2/mingw_64)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

file(GLOB_RECURSE EDITOR_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(${PROJECT_NAME} editorEntryPoint.cpp ${EDITOR_SRC_FILES})

message(STATUS ${Qt6_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE .)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)