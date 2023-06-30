project(GameEngineEditor)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC)
set(CMAKE_WIN32_EXECUTABLE TRUE)

set(CMAKE_PREFIX_PATH D:/QT/6.4.2/mingw_64)
find_package(Qt6 REQUIRED COMPONENTS 
    Core 
    Gui 
    Widgets
    OpenGLWidgets
)
message(STATUS ${Qt6Widgets_INCLUDE_DIRS})
qt_standard_project_setup()

file(GLOB_RECURSE EDITOR_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)
# 為了moc，必須參與編譯
file(GLOB_RECURSE EDITOR_HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*/*.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*/*/*.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*/*/*.hpp
)

file(GLOB_RECURSE QT_PLUGINS
    ${CMAKE_CURRENT_SOURCE_DIR}/plugins/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/plugins/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/plugins/*.h
)

list(REMOVE_ITEM SRC_FILES ${CMAKE_SOURCE_DIR}/src/GameBase.cpp)

add_executable(${PROJECT_NAME} 
    editorEntryPoint.cpp 
    mainwindow.ui
    mainwindow.qrc
    mainwindow.cpp
    ${QT_PLUGINS}
    ${EDITOR_HEADER_FILES}
    ${EDITOR_SRC_FILES}
    ${SRC_FILES}
    ${THIRD_PARTY_SRC}
)

# WIN32_EXECUTABLE 會使console消失
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE OFF
        MACOSX_BUNDLE ON
    )
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
    )
endif ()

target_include_directories(${PROJECT_NAME} PRIVATE .)
target_include_directories(${PROJECT_NAME} PRIVATE ./include)
target_include_directories(${PROJECT_NAME} PRIVATE ./plugins)
target_include_directories(${PROJECT_NAME} PRIVATE ${Qt6Widgets_INCLUDE_DIRS})
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