project(GameEngineEditor)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_WIN32_EXECUTABLE TRUE)

set(CMAKE_PREFIX_PATH D:/QT/6.4.2/mingw_64)
find_package(Qt6 REQUIRED COMPONENTS 
    Core 
    Gui 
    Widgets
    OpenGLWidgets
)
qt_standard_project_setup()

file(GLOB_RECURSE EDITOR_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

list(REMOVE_ITEM SRC_FILES ${CMAKE_SOURCE_DIR}/src/GameBase.cpp)

add_executable(${PROJECT_NAME} 
    editorEntryPoint.cpp 
    mainwindow.ui
    mainwindow.cpp
    ${EDITOR_SRC_FILES}
    ${SRC_FILES}
    ${THIRD_PARTY_SRC}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

target_include_directories(${PROJECT_NAME} PRIVATE .)
target_include_directories(${PROJECT_NAME} PRIVATE ./include)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    Qt6::Core 
    Qt6::Gui 
    Qt6::Widgets
    Qt6::OpenGLWidgets
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    GLEW::GLEW
)

add_custom_target(
    gameEngineEditor_copy_target ALL
    DEPENDS copy_qss
)

add_custom_command(
    OUTPUT copy_qss
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/qss
            ${CMAKE_CURRENT_BINARY_DIR}/qss
    DEPENDS always_rebuild
)

add_custom_command(
    OUTPUT always_rebuild
    COMMAND cmake -E echo "copy files"
)