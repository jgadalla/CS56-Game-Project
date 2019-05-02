#pragma once

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#endif

#include <cstdio>
#include <iostream>

#include "LTexture.hpp"

using namespace std;


enum MOTION {RIGHT, LEFT, UP, DOWN};

class Unit
{
protected:
  bool alive;
  int x;
  int y;
  float speedx;
  float speedy;
  int width;
  int height;

  LTexture* unitTexture;

public:
  Unit(LTexture* image, float x, float y);
  Unit();
  virtual ~Unit();
  void SetAlive(bool);
  bool GetAlive();
  int GetWidth();
  int GetHeight();
  float GetX();
  float GetY();
  virtual void Move(int direction);
  virtual void Move();
  virtual void Render( SDL_Renderer* gRenderer, bool debug);
  virtual void Render( SDL_Renderer* gRenderer);
};



