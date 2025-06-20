#ifndef GAME_LAUNCHER_H
#define GAME_LAUNCHER_H

#include "Core/GameBase.h"

#include "Scene/Scene.h"
#include <string>

class GameLauncher: public GameEngine::GameBase
{
public:
    GameEngine::Scene* scene;
    std::string currPath;
    
    GameLauncher(const char* title, int width, int height, const std::string& currPath);
    bool initAll();
    void parseProject(const std::string& projectName);

    virtual void gameEventHandle() override;
    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void startGame() override;
};

#endif