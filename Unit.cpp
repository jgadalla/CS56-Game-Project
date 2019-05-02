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
  // should call descustrocutor
}

bool Unit::GetAlive()
{
  return alive;
}


void Unit::Move(int direction)
{

if(allowMove){

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
}

void allowsMove(string direction){
  if(direction==LEFT)
    {
      if(x == XMID and y == YMID) allowsMove_ = false;
    }

  else if(direction==RIGHT)
    {
      if(x == XMID and y == YMID) allowsMove_ = false;
    }

  else if(direction==UP)
    {
      if(x == XMID  and y == YMID) allowsMove_ = false;
    }

  else
    {
      if(x == XMID and y == YMID) allowsMove_ = false;
    }

    allowMove_ = true;

}

void Unit::Move()
{
  ++y;
  if (y > 900){
    SetAlive(false);
  }
}

void Unit::Render(SDL_Renderer* gRenderer, bool debug)
{
  unitTexture->render( x, y, unitTexture->getTexRect(x,y), 0.0, NULL, SDL_FLIP_NONE, gRenderer );
  if(debug == true)
    {
      SDL_Rect rect = { x - width/2, y - height/2, width, height };
      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
      SDL_RenderDrawRect( gRenderer, &rect );
    }
}

void Unit::Render(SDL_Renderer* gRenderer){
  unitTexture->render(x,y,gRenderer);
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
