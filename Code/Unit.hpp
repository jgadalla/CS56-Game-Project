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
#include "finalConst.hpp"

using namespace std;


enum MOTION {RIGHT, LEFT, UP, DOWN};

class Unit{
protected:
  bool alive;
  int x;
  int y;
  float speedx;
  float speedy;
  int width;
  int height;
  bool allowsMove_;
  int direction_;
  bool keydown_;
  bool collision_;

  LTexture* unitTexture;

public:
  Unit(LTexture* image, int direction);
  Unit();
  virtual ~Unit();
  void SetAlive(bool name);
  bool GetAlive();
  int GetWidth();
  int GetHeight();
  float GetX();
  float GetY();
  int GetDirection();
  void allowsMove();
  void moveOn();
  void setKey();
  void crashed();
  void changeSpeed(int speed);
  SDL_Rect* getUnitRect();
  virtual void Move();
  virtual void Render( SDL_Renderer* gRenderer, bool debug);
  virtual void Render( SDL_Renderer* gRenderer);
};



