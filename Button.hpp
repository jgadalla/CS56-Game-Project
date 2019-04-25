#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>

class Button
{
public:
  // Set texture, button text, and upper left corner for rendering.
  Button(int x, int y);
  void render(SDL_Renderer* renderer);  // render using renderer.
  void setPosition(int x, int y);  // set upper left corner.
  SDL_Rect getRect();
private:
  int x, y;   // upper left corner for rendering.
  SDL_Rect btnRect;  // the rendering rectangle.
  //LTexture* btnTexture;  // texture.
};