#include"Car.hpp"

Car::Car(){}

Car::~Car()
{
  cout<<"Car Deallocated"<<endl;
}

Car::Car(LTexture* image, float x, float y):Unit(image, x, y)
{

  //generate random dir
    switch (rand() % 4)
    {
    //east   
    case 1:
        dir = 90;
        this->x = x + 10;
        this->y = y/2 - 40;
        break;
    //south
    case 2:
        dir = 180;
        this->x = x/2 + 10;
        this->y = y + 10;
        break;
    //west   
    case 3:
        dir = -90;
        this->x = 0 - 10;
        this->y = y/2 + 5;
        break;	   
    //north
    default:
        dir = 0;
        this->x = x/2 - 35;
        this->y = 0 - 10;
        break;
    }


  spriteSheetTexture = image;
  this->width = image->GetWidth();
  this->height = image->GetHeight();

}


void Car::Move(bool n_stop, bool e_stop, bool s_stop, bool w_stop)
{
    switch (dir)
    {
    //east   
    case 90:
        if(e_stop == false){
            x = x - 1;
            if(x < 0){
                SetAlive(false); // could use this to track score or on clean function 
            }
        }else{
            if(this->GetX() < 505){
                x = x - 1;
                if(x < 0){
                    SetAlive(false); // could use this to track score or on clean function
                }
            }else{
                if(this->GetX() > 505){
                    if(this->GetP() == false){
                        x = x - 1;
                    }       
                }
            }   
        }
        break;
    //south
    case 180:
        if(s_stop == false){
            y = y - 1;
            if(y < 0){
                SetAlive(false);
            }
        }else{
            if(this->GetY() < 338){
                y = y - 1;
                if(y < 0){
                    SetAlive(false);
                }
            }else{
                if(this->GetY() > 338){
                    if(this->GetP() == false){
                        y = y - 1;
                    }
                }
                
            }
        }
        break;
    //west   
    case -90:
        if(w_stop == false){
            x = x + 1;
            if(x > 792){
                SetAlive(false);
            }
        }else{
            if(this->GetX() > 262){
                x = x + 1;
                if(x > 792){
                    SetAlive(false);
                }
            }else{
                if(this->GetX() < 262){
                    if(this->GetP() == false){
                        x = x + 1;
                    }
                }
            }
        }
        
        break;	   
    //north
    default:
        if(n_stop == false){
            y = y + 1; 
            if(y > 468) {
                SetAlive(false);
            }
        }else{
            if(this->GetY() > 92){
                y = y + 1;
                if(y < 0){
                    SetAlive(false);
                }
            }else{
                if(this->GetY() < 92){
                    if(this->GetP() == false){
                        y = y + 1;
                    }
                }
            }
        }    
        break;
    }
}


void Car::Render(SDL_Renderer* gRender)
{
  spriteSheetTexture->Render(x, y, gRender, dir);
}