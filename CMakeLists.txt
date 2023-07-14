cmake_minimum_required(VERSION 3.16)

add_subdirectory(./GameEngine)
add_subdirectory(./gameEngineEditor)
add_subdirectory(./TestGame)

add_dependencies(GameEngineEditor GameEngine)
add_dependencies(TestGame GameEngine)