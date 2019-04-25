#include "Unit.hpp"

Unit::Unit()
{

}

Unit::Unit(LTexture* image, float x, float y)
{
  unitTexture = image;

  this->x = x;
  this->y = y;

  this->width = image->getWidth();
  this->height = image->getHeight();

  speedx = 0;
  speedy = 0;
  alive  = true;
}


Unit::~Unit()
{
  unitTexture = NULL;
}

void Unit::SetAlive(bool alive)
{
  this->alive = alive;
}

bool Unit::GetAlive()
{
  return alive;
}

void Unit::Move(int direction)
{

  if(direction==LEFT)
    {
      speedx = -5;
      x+=speedx;
    }

  if(direction==RIGHT)
    {
      speedx = 5;
      x+=speedx;
    }

  if(direction==UP)
    {
      speedy = -5;
      y+=speedy;
    }

  if(direction==DOWN)
    {
      speedy = 5;
      y+=speedy;
    }

}

void Unit::Move()
{
  x = x + speedx;
  y = y + speedy;
}

void Unit::Render(long int& frame, SDL_Renderer* gRenderer, bool debug)
{
  unitTexture->render( x - width/2, y - height/2, unitTexture->getTexRect(x,y), 0.0, NULL, SDL_FLIP_NONE, gRenderer );
  if(debug == true)
    {
      SDL_Rect rect = { x - width/2, y - height/2, width, height };
      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
      SDL_RenderDrawRect( gRenderer, &rect );
    }
}

int Unit::GetWidth()
{
  return width;
}

int Unit::GetHeight()
{
  return height;
}

float Unit::GetX()
{
  return x;
}
float Unit::GetY()
{
  return y;
}
