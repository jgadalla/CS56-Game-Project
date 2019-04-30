// #pragma once

// #ifdef __APPLE__
// #include <SDL2/SDL.h>
// #else
// #include <SDL.h>
// #endif


// class Unit
// {
// public:
// 	Unit(Texture* texture, SDL_Rect* hitbox);
// 	void getSpeed();
// 	virtual draw() = 0;
// 	void getTexture();
// 	void getRect();
// private:
// 	Texture* texture_;
// 	SDL_Rect* hitbox_;
// 	int speed;

// };
#pragma once

 #include <SDL2/SDL.h>
 #include <SDL2_image/SDL_image.h>
 #include <stdio.h>


#include <cstdio>
#include <iostream>

#include"LTexture.hpp"

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
  float friction; //lower speed means more friction

  enum ANIMATION_FRAMES {FLYING_FRAMES = 3};
  SDL_Rect spriteClips[ FLYING_FRAMES ];
  LTexture* spriteSheetTexture;

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
  virtual void Render(long int& frame, SDL_Renderer* gRenderer, bool debug);
  virtual void Render(SDL_Renderer* gRenderer);
};



