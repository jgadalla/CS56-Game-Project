#include "Unit.hpp"

Unit::Unit(){}

Unit::Unit(LTexture* image, float x, float y)
{

   spriteSheetTexture = image;
  this->width = image->GetWidth();
  this->height = image->GetHeight();

  friction = 0.95f;
  speedx = 0;
  speedy = 0;
  alive  = true;
  front = false;
}


Unit::~Unit()
{
  spriteSheetTexture = NULL;
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
  speedx = speedx * friction;
  speedy = speedy * friction;

  x = x + speedx;
  y = y + speedy;
}

void Unit::Move(bool n_stop, bool e_stop, bool s_stop, bool w_stop){}

void Unit::Render(SDL_Renderer* gRenderer )
{
  spriteSheetTexture->Render(x, y, gRenderer, dir);
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

int Unit::GetDir(){
  return dir;
}

bool Unit::GetP(){
  return front;
}

void Unit::setP(bool b){
  front = b;
}