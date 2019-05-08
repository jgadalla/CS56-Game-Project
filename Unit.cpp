#include "Unit.hpp"

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 640;

const float INTER_DOWN_Y = 210;
const float INTER_UP_Y = 390;
const float INTER_LEFT_X = 620;
const float INTER_RIGHT_X = 440;

Unit::Unit()
{

}

Unit::Unit(LTexture* image, float x, float y, int direction)
{
  unitTexture = image;

  this->x = x;
  this->y = y;

  this->width = image->getWidth();
  this->height = image->getHeight();

  mDirection = direction;

  speedx = 5;
  speedy = 5;
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

void Unit::Stop(){
  speedx = 0;
  speedy = 0;
  stopped = true;
}

bool Unit::Stopped(){
  switch (mDirection)
  {
    case RIGHT:
      if(this->x == INTER_RIGHT_X){
        Stop();
      }
      break;

    case LEFT:
      if(this->x == INTER_LEFT_X){
        Stop();
      }
      break;
    case UP:
      if(this->y == INTER_UP_Y){
        Stop();
      }
      break;
    case DOWN:
      if(this->y == INTER_DOWN_Y){
        Stop();
      }
      break;
  
    default:
      break;
  }
  return stopped;
}

bool Unit::getStopped(){
  return stopped;
}

void Unit::Go(){
  speedx = 10;
  speedy = 10;
}

void Unit::Move(int direction)
{

  if (direction == LEFT)
  {
    x -= speedx;
    if (x < -50)
    {
      SetAlive(false);
    }
  }

  if (direction == RIGHT)
  {
    x += speedx;
    if (x > 550)
    {
      SetAlive(false);
    }
  }

  if (direction == UP)
  {
    y -= speedx;
    if (y < -50)
    {
      SetAlive(false);
    }
  }

  if (direction == DOWN)
  {
    y += speedy;
    if (y > 900)
    {
      SetAlive(false);
    }
  }
}


int Unit::getDirection(){
  return mDirection;
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
  unitTexture->render(x,y,gRenderer, mDirection);
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
