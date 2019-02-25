#include "Actor.h"
#include "StudentWorld.h"
#include "GameWorld.h"
#include "GameConstants.h"

#include <iostream>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imgID, double x, double y, StudentWorld* sw, int dir, int depth):GraphObject(imgID, x, y)
{

    swptr = sw;
}
Actor::~Actor()
{
    
}

void Actor::doSomething()
{
    
}

bool Actor::blocksMovement() const
{
    return false;
}

bool Agent::blocksMovement() const
{
    return true;
}

bool Wall::blocksMovement() const
{
    return true;
}

StudentWorld* Actor:: getWorld() const

{
    return swptr;
}

bool Actor::checkActorMove(double x, double y, Actor* self)
{
    return(swptr->blockCheck(x, y, this));
}

ActivatingObject::ActivatingObject(int imageID, double x, double y, StudentWorld* sw, int direction, int depth): Actor (imageID, x, y, sw, direction, depth)
{
    
}

Exit::Exit(double x, double y, StudentWorld* sw): ActivatingObject(10, x, y, sw, right, 1)
{

}

Agent::Agent(int imageID, double x, double y, StudentWorld* sw, int dir): Actor (imageID, x, y, sw, right, 0)
{
    
}

Citizen::Citizen(double x, double y, StudentWorld* sw):Human(2, x, y, sw)
{
    m_alive = true;
}

void Citizen::doSomething()
{
    
}

void Citizen::dieByFallOrBurnIfAppropriate()
{
    cout<<"here??";
    getWorld()->recordCitizenGone(this);
}

Human::Human(int imageID, double x, double y, StudentWorld* sw): Agent(imageID, x, y, sw, right)
{
    m_infectedStatus = false;
    m_infectionCount = 0;
}


Penelope::Penelope(double x, double y, StudentWorld* sw): Human(0, x, y, sw)
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

Wall::Wall(int imgID, int x, int y, StudentWorld* sw): Actor(imgID, x, y, sw, right, 0)
{
    
}

void Exit::doSomething()
{
    StudentWorld* sw = getWorld(); //Creates a new pointer to the student world
    if (sw->touching(this, sw->getPenelopePointer())) //Checks if the wall and penelope are touching
    {
        if (sw->noMoreCitizens())
            sw->SetLevelCompleted(true);
    }
}

Wall::~Wall()
{
    
}




