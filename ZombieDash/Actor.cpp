#include "Actor.h"
#include "StudentWorld.h"

#include <iostream>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
  
Penelope::Penelope(int imgID, int x, int y ): Actor(imgID, x, y)
{
    
}

Wall::Wall(int imgID, int x, int y ): Actor(imgID, x, y)
{
    
}

Wall::~Wall()
{
    
}


Penelope::~Penelope()
{
    
}

Actor::Actor(int imgID, int x, int y):GraphObject(imgID, x, y)
{
    
}
Actor::~Actor()
{
    
}
