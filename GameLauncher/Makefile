# Output file name
ExecutionFilename = GameLauncher

ROOT_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

GameEngineInclude = $(ROOT_DIR)../GameEngine/include
GameEngineThirdParty = $(ROOT_DIR)../GameEngine/third_party
Box2dInclude = $(ROOT_DIR)../GameEngine/third_party/box2d/include
GameLauncherInclude = $(ROOT_DIR)include
GameLauncherSrc = $(ROOT_DIR)src/*.cpp
GameEngineStaticLib = $(ROOT_DIR)../GameEngine/lib

ALL_INCLUDE = -I $(GameEngineInclude) -I $(GameLauncherInclude) -I $(GameEngineThirdParty) -I $(Box2dInclude)
ALL_Lib = -lbox -lGameEngine

all: entryPoint.cpp
	g++ entryPoint.cpp $(GameLauncherSrc) $(ALL_INCLUDE) $(GameEngineStaticLib) -o $(ExecutionFilename).exe