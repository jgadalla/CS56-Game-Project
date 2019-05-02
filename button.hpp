#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

class Button
{
public:
  // Set texture, button text, and upper left corner for rendering.
  Button(LTexture* Texture, std::string str, int x, int y);
  void render(SDL_Renderer* renderer);  // render using renderer.
  void setPosition(int x, int y);  // set upper left corner.
  void setText(std::string str);  // set button text.
private:
  Text* text;  // Button text.
  int x, y;   // upper left corner for rendering.
  SDL_Rect btnRect;  // the rendering rectangle.
  LTexture* btnTexture;  // texture.
};