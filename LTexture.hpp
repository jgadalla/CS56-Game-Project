#pragma once
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <cstdio>
#include <iostream>

//Texture wrapper class
class LTexture
{
private:
  SDL_Texture* texture;
  int width;
  int height;
public:
  //constructor and destructor
  LTexture();   
  ~LTexture(); 
  
  //Load surface to turn into texture
  bool LoadFromFile( std::string path, SDL_Renderer* gRenderer );  

  //Deallocates texture
  void Free();    

  //render texture 
  void Render(int x, int y, SDL_Renderer* gRenderer);

  //render texture with direction and orientation
  void Render(int x, int y, SDL_Renderer* gRenderer, int dir);

  //Get texture Width and Height
  int GetWidth();
  int GetHeight();

};
