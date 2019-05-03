#include"Queue.hpp"
#include<iostream>


using namespace std;

Queue::Queue()
{
  head = NULL;
  tail = NULL;
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


//render w
void Queue::Render(SDL_Renderer* gRenderer) {
  Node* temp = head;
    while (temp!=NULL)
    {
      temp->unit->Render(gRenderer);
      temp=temp->next;
    }
    
}

void Queue::Move(bool n_stop, bool e_stop, bool s_stop, bool w_stop)
{
  Node* temp = head;
  while(temp!=NULL)
    {

      float tempX = temp->unit->GetX();
      float tempY = temp->unit->GetY();
      int tempDir = temp->unit->GetDir();
      Node* currentTemp = temp;
    
      while(currentTemp != head){
        Node* prevCar = currentTemp->prev;
        int prevCarDir = prevCar->unit->GetDir();

        if(prevCarDir == tempDir){
          float prevCarX = prevCar->unit->GetX();
          float prevCarY = prevCar->unit->GetY();
          float diff;
        
          switch (tempDir)
          { 
              //North
            case 0:
              diff = prevCarY - tempY;
              if(diff < 50.0){
                temp->unit->setP(true);
              }else{
                temp->unit->setP(false);
              }
              break;
              //East
            case 90:
              diff = tempX - prevCarX;
              if(diff < 50.0){
                temp->unit->setP(true);
              }else{
                temp->unit->setP(false);
              }
              break;
              //South
            case 180:
              diff = tempY - prevCarY;
              if(diff < 50.0){
                temp->unit->setP(true);
              }else{
                temp->unit->setP(false);
              }
              break;
              //West
            case -90:
              diff = prevCarX - tempX;
              if(diff < 50.0){
                temp->unit->setP(true);
              }else{
                temp->unit->setP(false);
              }
              break;
          }
          break;
        }else{
          currentTemp = currentTemp->prev;
        }
        
      }

      temp->unit->Move(n_stop, e_stop, s_stop, w_stop);
      temp=temp->next;
    }
}
