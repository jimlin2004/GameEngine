#include "Graphics.h"

//以下為Color的函數實現

GameEngine::Graphics::Color::Color(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

//以下為Graphics(圖形基類)的函數實現

GameEngine::Graphics::Graphics::Graphics()
{
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
    this->color = new Color(1.f, 1.f, 1.f, 1.f);
}

GameEngine::Graphics::Graphics::Graphics(float x, float y)
{
    this->x = x;
    this->y = y;
    this->width = 0;
    this->height = 0;
    this->color = new Color(1.f, 1.f, 1.f, 1.f);
}

GameEngine::Graphics::Graphics::Graphics(float x, float y, Color* color)
{
    this->x = x;
    this->y = y;
    this->width = 0;
    this->height = 0;
    this->color = color;
}

GameEngine::Graphics::Graphics::Graphics(float x, float y, float width, float height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->color = new Color(1.f, 1.f, 1.f, 1.f);
}

GameEngine::Graphics::Graphics::Graphics(float x, float y, float width, float height, Color* color)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->color = color;
}

float GameEngine::Graphics::Graphics::getX()
{
    return this->x;
}

void GameEngine::Graphics::Graphics::setX(float x)
{
    this->x = x;
    return;
}

float GameEngine::Graphics::Graphics::getY()
{
    return this->y;
}

void GameEngine::Graphics::Graphics::setY(float y)
{
    this->y = y;
    return;
}

void GameEngine::Graphics::Graphics::render()
{
    return;
}

//end of Graphics(圖形基類)

//以下為Rect(矩形)的函數實現

GameEngine::Graphics::Rect::Rect(): Graphics()
{
    return;
}

GameEngine::Graphics::Rect::Rect(float x, float y): Graphics(x, y)
{
    return;
}

GameEngine::Graphics::Rect::Rect(float x, float y, Color* color): Graphics(x, y, color)
{
    return;
}

GameEngine::Graphics::Rect::Rect(float x, float y, float width, float height): Graphics(x, y, width, height)
{
    return;
}

GameEngine::Graphics::Rect::Rect(float x, float y, float width, float height, Color* color): Graphics(x, y, width, height, color)
{
    return;
}

void GameEngine::Graphics::Rect::render()
{
    float x2 = this->x + this->width;
    float y2 = this->y + this->height;
    glColor3f(this->color->r, this->color->g, this->color->b);
    glBegin(GL_QUADS);
        glVertex3f(this->x, this->y, 0.0f);
        glVertex3f(x2, this->y, 0.0f);
        glVertex3f(x2, y2, 0.0f);
        glVertex3f(this->x, y2, 0.0f);
    glEnd();
    return;
}

GameEngine::Graphics::Image::Image(float x, float y): Graphics(x, y)
{
    return;
}

/*用於載入圖片，支持png、jpg*/
void GameEngine::Graphics::Image::loadImage(const char* fileName)
{
    SDL_Surface* _image = IMG_Load(fileName);
    if (!_image)
        throw "Image can't be loaded";
    this->width = _image->w;
    this->height = _image->h;
    this->nrChannels = _image->format->BitsPerPixel / 8;

    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _image->pixels);
}

/*以下為Graphics處理時用的function*/
void filpSurface(SDL_Surface* surface)
{
    SDL_LockSurface(surface);

    int pitch = surface->pitch; //row size
    char* temp = new char[pitch]; //intermediate buffer
    char* pixels = (char*)surface->pixels;
    char* row1;
    char* row2;
    for (int i = 0; i < surface->h / 2; ++i)
    {
        row1 = pixels + i * pitch;
        row2 = pixels + (surface->h - i - 1) * pitch;

        //swap rows
        memcpy(temp, row1, pitch);
        memcpy(row1, row2, pitch);
        memcpy(row2, temp, pitch);
    }
    delete[] temp;
    SDL_UnlockSurface(surface);
}