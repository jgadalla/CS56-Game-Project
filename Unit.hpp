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
  //direction
  int dir;      

  //is the unit on screen?                         
  bool alive;  
  //is there a another unit in proximity
  bool front;                          
  int x;
  int y;

  //horizontal speed and vertical speed
  float speedx;                         
  float speedy;	  

  //Height and width                      
  int height;
  int width;

  //lower speed means more friction
  float friction;      

  //Texture Unit
  LTexture* spriteSheetTexture;

public:

  //constructors
  Unit(LTexture* image, float x, float y);      
  Unit();    

  //destructor                                   
  virtual ~Unit();    

  void SetAlive(bool);                          
  bool GetAlive();   	 

  //Get width and height                         
  int GetWidth();		                            
  int GetHeight();

  //Get position 
  float GetX();		                            
  float GetY();

  //Get direction
  int GetDir();

  //get and set boolean front for proximity 
  bool GetP();
  void setP(bool b);



  //Move unit
  virtual void Move(int direction);             
  virtual void Move(bool n_stop, bool e_stop, bool s_stop, bool w_stop);    
  virtual void Move();                        

  //Render unit
  virtual void Render(SDL_Renderer* gRenderer);

};



