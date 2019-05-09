#include"Queue.hpp"
#include<iostream>

using namespace std;

Queue::Queue()
{
  head = NULL;
  tail = NULL;
  collision = false;
}

Queue::~Queue()
{
  while(head != NULL)
    {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
}

void Queue::Enqueue(Unit* unit)
{
  if(head == NULL)
    {
      head = new Node;
      head->unit = unit;
      head->next = NULL;
      head->prev = NULL;
      tail = head;
    }
  else
    {
      tail->next = new Node;
      tail->next->unit = unit;
      tail->next->next = NULL;
      tail->next->prev = tail;
      tail = tail->next;
    }
}

void Queue::Clean()
{
  Node* temp = head;
  while(temp!=NULL)
    {
      if(temp->unit->GetAlive() == false)
        {
	  if(temp->prev == NULL)
            {
	      head=head->next;
	      if(head!=NULL)
                {
		  head->prev = NULL;
                }
	      delete temp;
	      temp = head;
            }
	  else if(temp ->next == NULL)
            {
	      tail = tail->prev;
	      tail->next = NULL;
	      delete temp;
	      break;
            }
	  else
            {
	      Node* carry = temp->next;
	      temp->prev->next = temp->next;
	      temp->next->prev = temp->prev;
	      delete temp;
	      temp = carry;
            }
        }
      temp = temp->next;
    }
}

void Queue::Render(SDL_Renderer* gRenderer, bool debug)
{
  Node* temp = head;
  while(temp!=NULL)
    {
      temp->unit->Render(gRenderer, debug);
      temp->unit->Move();
      temp=temp->next;
    }
}

void Queue::Render(SDL_Renderer* gRenderer){
    Node* temp = head;
    while (temp!=NULL)
    {
      temp->unit->Render(gRenderer);
      temp->unit->Move();
      temp=temp->next;
    }
}

void Queue::checkCollision(Queue& other){
  Node* temp = head;
  SDL_Rect* curr = new SDL_Rect();
  while(temp != NULL){
    curr = temp->unit->getUnitRect();
    Node* temp2 = other.head;
    SDL_Rect* curr2 = new SDL_Rect();
    SDL_Rect colRect;
    while(temp2 != NULL){
      curr2 = temp2->unit->getUnitRect();
      if (SDL_IntersectRect(curr, curr2, &colRect) && temp->unit != temp2->unit){
        collision = true;
        break;
      }
      temp2 = temp2->next;
    }
    if (collision){
      break;
    }
    temp = temp->next;
    delete curr2;
  }
  delete curr;
}

bool Queue::getCol(){
  return collision;
}

void Queue::setKey()
{
  Node* temp = head;
  while(temp!=NULL)
    {
      temp->unit->setKey();
      temp=temp->next;
    }
}

void Queue::Move()
{
  Node* temp = head;
  while(temp!=NULL)
    {
      temp->unit->Move();
      temp=temp->next;
    }
}
