#include "Button.hpp"

Button::Button(int x, int y){
    btnRect.x = x;
    btnRect.y = y;
    btnRect.w = 208;
    btnRect.h = 57;
}

void Button::render(SDL_Renderer* renderer){
    SDL_RenderDrawRect(renderer, &btnRect);
}

void Button::setPosition(int newX, int newY){
    x = newX;
    y = newY;
}

SDL_Rect Button::getRect(){
    return btnRect;
}