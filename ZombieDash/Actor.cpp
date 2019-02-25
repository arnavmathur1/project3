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
    m_alive = true; //Citizens start out alive and on their first tick they are not paralysed
    m_paralysed = false;
}

void Citizen::doSomething()
{
    if (!m_alive)
        return; //When a citizen is dead this immediately returns. no modifications are made

    if (isParalysed())
    {
        m_paralysed = false;
        return;
    }
    
    m_paralysed = true; //Paralyses citizens every alternate tick in connjunction with the if statement above
    
    
    
    double dx = this->getX() - getWorld()->getPenelopePointer()->getX(); //Distance between citizen and Penelope
    double dy = this->getY() - getWorld()->getPenelopePointer()->getY();
    
    double dist_p = sqrt((dx*dx) + (dy*dy));
    
    if (dist_p<=80) //Checking this d is <80 pixels
    {
        if (getX() == getWorld()->getPenelopePointer()->getX() && dy<0)
        {
            /*
            setDirection(up);
            if(checkActorMove(getX(), getY()+2, this)) JUNK CODE IGNORE PLS
                moveTo(getX(), getY()+2);
            */
            moveHelper(getX(), getY()+2, up, this);
            return;
        }
        else if (getX() == getWorld()->getPenelopePointer()->getX() && dy>0)
        {
            moveHelper(getX(), getY()-2, down, this);
            /*setDirection(down);

            if(checkActorMove(getX(), getY()-2, this))
                moveTo(getX(), getY()-2);*/
        }
        

        else if (getY() == getWorld()->getPenelopePointer()->getY() && dx<0)
        {
            /*
            setDirection(right);
            if(checkActorMove(getX()+2, getY(), this))
                moveTo(getX()+2, getY());*/
             moveHelper(getX()+2, getY(), right, this);
            return;
        }
        else if (getY() == getWorld()->getPenelopePointer()->getY() && dx>0)
        {
            /*
            setDirection(left);
            if(checkActorMove(getX()-2, getY(), this))
                moveTo(getX()-2, getY());*/
             moveHelper(getX()-2, getY(), left, this);
            return;
        }
        
        else if (dy<0 && dx<0) //We now check each direction sequentially for the most appropriate citizen move based on its and Penelope's current position
        {
            int result = randInt(0, 1);
           
            if (result == 0) //Checking if up is valid
            {
                if(checkActorMove(getX(), getY()+2, this))
                {
                    moveHelper(getX(), getY()+2, up, this);
                }
            }
            else if (checkActorMove(getX()+2, getY(), this))
            {
                moveHelper(getX()+2, getY(), right, this);
            }
            return;
            
        }
        
        
        else if (dy>0 && dx<0)
        {
            int result = randInt(0, 1);
            
            if (result == 0)
            {
                if(checkActorMove(getX(), getY()-2, this))
                {
                    moveHelper(getX(), getY()-2, down, this);
                }
            }
            else if (checkActorMove(getX()+2, getY(), this))
            {
                moveHelper(getX()+2, getY(), right, this);
            }
            return;
            
        }
        
        else if (dy<0 && dx>0)
        {
            int result = randInt(0, 1);
            
            if (result == 0) //Checking if up is valid
            {
                if(checkActorMove(getX(), getY()+2, this))
                {
                    moveHelper(getX(), getY()+2, up, this);
                }
            }
            else if (checkActorMove(getX()-2, getY(), this))
            {
                moveHelper(getX()+2, getY(), left, this);
            }
            return;
            
        }
        
        else if (dy>0 && dx>0)
        {
            int result = randInt(0, 1);
            
            if (result == 0) //Checking if up is valid
            {
                if(checkActorMove(getX(), getY()-2, this))
                {
                    moveHelper(getX(), getY()-2, down, this);
                }
            }
            else if (checkActorMove(getX()-2, getY(), this))
            {
                moveHelper(getX()-2, getY(), left, this);
            }
            return;
        }
        
        return;
    }
}

void Agent::moveHelper(double x, double y,int dir, Actor *ap)
{
    setDirection(dir); //A movement function that can handle Agent movemennt
    if(checkActorMove(x, y, this))
        moveTo(x, y);
}

void Citizen::dieByFallOrBurnIfAppropriate()
{
    cout<<"here??";
    getWorld()->recordCitizenGone(this);
}

bool Citizen::isParalysed()
{
    if (m_paralysed) //Checks whether a citizen is already paralysed
        return true;
    return false;
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
                moveHelper(getX(), getY()+4, up, this); //Works identically to citizens
                
                return;
            case KEY_PRESS_DOWN:
                moveHelper(getX(), getY()-4, down, this);
               
                return;
            case KEY_PRESS_LEFT:
                moveHelper(getX()-4, getY(), left, this);
                return;
            case KEY_PRESS_RIGHT:
                moveHelper(getX()+4, getY(), right, this);
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
    if (touching(this, sw->getPenelopePointer())) //Checks if the wall and penelope are touching
    {
        if (sw->noMoreCitizens()) //When we are out of citizens (i.e. all safe/dead) the level has been completed and the exit functionality can be activated
            sw->SetLevelCompleted(true);
    }
}

bool Actor::canUseExit()
{
    return false;
}

bool Human::canUseExit()
{
    return true;
}

Wall::~Wall()
{
    
}

bool Actor::touching(Actor *a1, Actor *a2)
{
    
    
    double dx = a1->getX() - a2->getX();
    double dy = a1->getY() - a2->getY();
    
    double distance = sqrt((dx*dx) + (dy*dy));
    //cout<<distance<<" ";
    if (distance <= 10)
    {
        return true;
    }
    
    return false;
}




