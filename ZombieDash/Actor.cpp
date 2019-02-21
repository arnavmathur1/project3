#include "Actor.h"
#include "StudentWorld.h"
#include "GameWorld.h"
#include "GameConstants.h"

#include <iostream>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imgID, int x, int y, StudentWorld* sw):GraphObject(imgID, x, y)
{

    swptr = sw;
}
Actor::~Actor()
{
    
}

void Actor::doSomething()
{
    
}

StudentWorld* Actor:: getWorld() const
{
    return swptr;
}

bool Actor::checkActorMove(double x, double y, Actor* self)
{
    return(swptr->blockCheck(x, y, this));
}

Penelope::Penelope(int imgID, int x, int y, StudentWorld* sw): Actor(imgID, x, y, sw)
{
    //setDirection(right);
    
    
}

Penelope::~Penelope()
{
    
}

void Penelope::doSomething()
{
    int keyPress = -1;
    
    if (getWorld()->getKey(keyPress)) //Implements algorithm from the "hint" section in footnote 4
    {
     
        
        switch (keyPress)
        {
            case KEY_PRESS_UP:
                setDirection(up);
                cout<<"UP";
                if(checkActorMove(getX(), getY()+4, this))
                    moveTo(getX(), getY()+4);
                return;
            case KEY_PRESS_DOWN:
                setDirection(down);
                
                if(checkActorMove(getX(), getY()-4, this))
                    moveTo(getX(), getY()-4);
                return;
            case KEY_PRESS_LEFT:
                setDirection(left);
                
                if(checkActorMove(getX()-4, getY(), this))
                    moveTo(getX()-4, getY());

                return;
            case KEY_PRESS_RIGHT:
                setDirection(right);
                
                if(checkActorMove(getX()+4, getY(), this))
                    moveTo(getX()+4, getY());
                return;
            default:
                break;
        }
    }
    
}

Wall::Wall(int imgID, int x, int y, StudentWorld* sw): Actor(imgID, x, y, sw)
{
    
}

Wall::~Wall()
{
    
}




