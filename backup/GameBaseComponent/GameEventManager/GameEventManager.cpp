#include "../include/GameBaseComponent/GameEventManager/GameEventManager.h"

GameEngine::GameEventManager::GameEventManager()
{
    return;
}

bool GameEngine::GameEventManager::checkIsKeyExists(int key)
{
    return (this->eventDatabase[EventType::KeyEvent].find(key) != this->eventDatabase[EventType::KeyEvent].end());
}

void GameEngine::GameEventManager::bindKeyEvent(int key, std::function<void(void)> func)
{
    if (this->checkIsKeyExists(key))
    {
        this->eventDatabase[EventType::KeyEvent].at(key).push_back(func);
    }
    else
    {
        this->eventDatabase[EventType::KeyEvent].insert({key, {}});
        this->eventDatabase[EventType::KeyEvent].at(key).push_back(func);
    }
}

void GameEngine::GameEventManager::callKeyEvent(int key)
{
    if (this->checkIsKeyExists(key))
    {
        for (std::function<void ()> event: this->eventDatabase[EventType::KeyEvent].at(key))
        {
            event();
        }
    }
}