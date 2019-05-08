#include "Unit.hpp"

Unit::Unit()
{

}

Unit::Unit(LTexture* image, int direction): 
unitTexture(image), direction_(direction), allowsMove_(true), keydown_(false), collision_(false), speedx(1), speedy(1), alive(true)
{
  this->width = image->getWidth();
  this->height = image->getHeight();

  switch(direction_){
    case NORTH:
      unitTexture->setAngle(180);
      x = XMID + 30;
      y = YMAX + 50;
      break;
    case EAST:
      //unitTexture->setAngle(90);
      x = -50;
      y = YMID + 30;
      break;
    case WEST:
      unitTexture->setAngle(270);
      x = XMAX + 50;
      y = YMID - 30;
      break;
    default:
          x = XMID - 30;
          y = -50;
  }

  this->width = unitTexture->getWidth();
  this->height = unitTexture->getHeight();

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


void Unit::Move()
{

allowsMove();

if(allowsMove_){

  if(direction_== WEST)
    {
      x -= speedx;
    }

  if(direction_== EAST)
    {
      x+= speedx;
    }

  if(direction_== NORTH)
    {
      y-= speedy;
    }

  if(direction_== SOUTH)
    {
      y += speedy;
    }

  }

  if (y > YMAX + 200 || x > XMAX + 200){
    SetAlive(false);
  }
}

void Unit::changeSpeed(int speed){
  if (direction_ == SOUTH || direction_ == NORTH){
      speedy = speed;
  }
  else{
      speedx = speed;
  }
}


void Unit::setKey(){

  if(direction_ == NORTH)
    {
      if(y < YMID + 80) keydown_ = true;
    }

  else if(direction_ == EAST)
    {
      if(x > XMID - 80) keydown_ = true;
    }

  else if(direction_ == WEST)
    {
      if(x < XMID + 80) keydown_ = true;

    }

  else 
    {
      if(y > YMID - 80) keydown_ = true;
    }


}

void Unit::crashed(){
  collision_ = true;
}

void Unit::allowsMove(){

if(collision_){
      changeSpeed(0);
      allowsMove_ = false;
}
else if(!allowsMove_ and keydown_){
      changeSpeed(5);
      allowsMove_ = true;
}
else{


  if(direction_ == NORTH)
    {
      if(y < YMID + 80) allowsMove_ = false;
    }

  else if(direction_ == EAST)
    {
      if(x > XMID - 80) allowsMove_ = false;
    }

  else if(direction_ == WEST)
    {
      if(x < XMID + 80) allowsMove_ = false;

    }

  else 
    {
      if(y > YMID - 80) allowsMove_ = false;
    }

  }
}

int Unit::GetDirection(){
  return direction_;
}

void Unit::Render(SDL_Renderer* gRenderer, bool debug)
{
  unitTexture->render( x, y, unitTexture->getTexRect(x,y), NULL, SDL_FLIP_NONE, gRenderer );
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
