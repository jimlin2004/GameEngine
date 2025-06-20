#include "GameLauncher.h"

#include <string>
#include <iostream>
#include <filesystem>
#include "json/json.hpp"


using Json = nlohmann::json;

int main(int argc, char* argv[])
{
    Json config;
    std::ifstream input("./config.json");
    input >> config;

    std::string gameName = config["window"]["title"];
    int windowWidth = config["window"]["width"];
    int windowHeight = config["window"]["height"];

    std::string currPath = std::filesystem::current_path().string();

    GameLauncher* launcher = new GameLauncher(gameName.c_str(), windowWidth, windowHeight, currPath);
    
    bool ok = launcher->initAll();
    launcher->parseProject(gameName);
    
    if (ok)
        launcher->startGame();
    return 0;
}