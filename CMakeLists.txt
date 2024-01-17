cmake_minimum_required(VERSION 3.16)

add_subdirectory(./GameEngine)
add_subdirectory(./GameEngineEditor)

add_dependencies(GameEngineEditor GameEngine)