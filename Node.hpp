#pragma once
#include "Unit.hpp"

struct Node
  {
    Unit* unit;
    Node* next;
    Node* prev;

    ~Node()
    {
      delete unit;
    }
};
