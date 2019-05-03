#pragma once

#include"Unit.hpp"

class Enemy:public Unit
  {
  public:
    Enemy(LTexture* image, float x, float y);
    Enemy();
    virtual ~Enemy();
    virtual void Move();
    virtual void Render(SDL_Renderer* gRenderer);
};
