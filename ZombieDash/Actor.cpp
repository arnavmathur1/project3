#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

#include <iostream>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imgID, int x, int y):GraphObject(imgID, x, y)
{
    
}
Actor::~Actor()
{
    
}

void Actor::doSomething()
{
    
}

Penelope::Penelope(int imgID, int x, int y ): Actor(imgID, x, y)
{
    setDirection(right);
    
    
}

Penelope::~Penelope()
{
    
}

void Penelope::doSomething(int keyPress)
{
    cout<<keyPress;
    
    if(keyPress == -1)
        return;
    
    switch (keyPress)
    {
        case KEY_PRESS_UP:
            setDirection(up);
            break;
        case KEY_PRESS_DOWN:
            setDirection(down);
            break;
        case KEY_PRESS_LEFT:
            setDirection(left);
            break;
        case KEY_PRESS_RIGHT:
            setDirection(right);
            break;
        default:
            break;
    }
    
    
    if (getDirection() == up)
    {
        
        moveTo(getX(), getY()+4);
    }
   
    if (getDirection() == down)
    {
        moveTo(getX(), getY()-4);
    }

    if (getDirection() == right)
    {
        moveTo(getX()+4, getY());
    }
    
    if (getDirection() == left)
    {
        moveTo(getX()-4, getY());
    }
    
    //setDirection(0);
}

Wall::Wall(int imgID, int x, int y ): Actor(imgID, x, y)
{
    
}

Wall::~Wall()
{
    
}




