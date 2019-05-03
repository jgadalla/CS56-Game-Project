#pragma once

#include"Unit.hpp"

class Car:public Unit
  {
  public:
    Car(LTexture* image, float x, float y);
    Car();
    virtual ~Car();
    virtual void Move(bool n_stop, bool e_stop, bool s_stop, bool w_stop);
    virtual void Render(SDL_Renderer* gRenderer);

};
