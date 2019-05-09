// #pragma once
// #include "Node.hpp"

#pragma once
#include "Node.hpp"

class Queue
  {
  private:
    Node* head;
    Node* tail;
    bool collision;

  public:
    Queue();
    ~Queue();
    void Enqueue(Unit*);
    void Clean();
    void Render(SDL_Renderer* gRenderer, bool debug);
    void Render(SDL_Renderer* gRenderer);
    void Move();
    void checkCollision(Queue& other);
    void setKey();
    bool getCol();
};
