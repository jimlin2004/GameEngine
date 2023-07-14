#include "Event/Input.h"

namespace GameEngine
{
    const uint8_t* GameEngine::Input::keyboardState = SDL_GetKeyboardState(NULL);
}

GameEngine::MousePosition::operator glm::vec2()
{
    return glm::vec2{this->x, this->y};
}

bool GameEngine::Input::isKeyPressed(KeyCode keyCode)
{
    return Input::keyboardState[keyCode];
}

bool GameEngine::Input::isMouseButtonPressed(MouseCode mouseCode)
{
    return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(mouseCode);
}

GameEngine::MousePosition GameEngine::Input::getMousePosition()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    return MousePosition{x, y};
}

void GameEngine::Input::getMousePosition(int *x, int *y)
{
    SDL_GetMouseState(x, y);
}

int GameEngine::Input::getMouseX()
{
    int x;
    SDL_GetMouseState(&x, NULL);
    return x;
}

void GameEngine::Input::getMouseX(int *x)
{
    SDL_GetMouseState(x, NULL);
}

int GameEngine::Input::getMouseY()
{
    int y;
    SDL_GetMouseState(NULL, &y);
    return y;
}

void GameEngine::Input::getMouseY(int *y)
{
    SDL_GetMouseState(NULL, y);
}
