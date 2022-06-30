cmake_minimum_required(VERSION 3.0.0)
project(Arkanoid VERSION 0.1.0)

include(CTest)
enable_testing()

set(SDL2_INCLUDE_DIRS E:/cpp_lib/SDL2-devel-2.0.22-VC/SDL2-2.0.22/include)
set(SDL2_LIBRARIES E:/cpp_lib/SDL2-devel-2.0.22-VC/SDL2-2.0.22/lib/x64)
include_directories(${SDL2_INCLUDE_DIRS})
link_directories(${SDL2_LIBRARIES})

file(GLOB_RECURSE SRC_FILE src/*.cpp)
add_executable(Arkanoid main.cpp ${SRC_FILE})
target_link_libraries(Arkanoid SDL2main SDL2)
target_include_directories(Arkanoid PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
