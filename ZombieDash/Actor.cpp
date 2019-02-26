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
            return;
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
    if (getWorld()->touching(this, sw->getPenelopePointer())) //Checks if the wall and penelope are touching
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






//Zombies
Zombie::Zombie(double x, double y, StudentWorld* sw): Agent(1, x, y, sw, right)
{
    m_alive = true;
    m_paralysed = false;
    m_movementPlan = 0;
}

SmartZombie::SmartZombie(double x, double y, StudentWorld* sw):Zombie(x,y,sw)
{}

DumbZombie::DumbZombie(double x, double y, StudentWorld* sw):Zombie(x,y,sw)
{
    
    
}

void DumbZombie::doSomething()
{
    if (!isAlive())
        return; //When a citizen is dead this immediately returns. no modifications are made
    
    if (isParalysed())
    {
        setParalysed(false);
        return;
    }
    
    setParalysed(true); //Paralyses citizens every alternate tick in connjunction with the if statement above
    
    if (movementsLeft() == 0)
    {
        newMovement(randInt(3, 10));
       
        int dir = randInt(0, 3);
        switch (dir)
        {
            case 0:
                setDirection(right);
                break;
            case 1:
                setDirection(left);
                break;
            case 3:
                setDirection(down);
                break;
            case 2:
                setDirection(up);
                break;
            default:
                break;
        }
    }
    if (movementsLeft()>0)
    {
        switch (getDirection())
        {
            case right:
                if (checkActorMove(getX()+1, getY(), this))
                {
                    moveHelper(getX()+1, getY(), right, this);
                }
                else
                {
                    newMovement(0);
                }
                break;
            case left:
                if (checkActorMove(getX()-1, getY(), this))
                {
                    moveHelper(getX()-1, getY(), left, this);
                }
                else
                {
                    newMovement(0);
                }
                break;
            case up:
                if (checkActorMove(getX(), getY()+1, this))
                {
                    moveHelper(getX(), getY()+1, up, this);
                }
                else
                {
                    newMovement(0);
                }
                break;
            case down:
                if (checkActorMove(getX(), getY()-1, this))
                {
                    moveHelper(getX(), getY()-1, down, this);
                }
                else
                {
                    newMovement(0);
                }
                break;
            default:
                break;
        }
        if (movementsLeft()!=0)
            newMovement(movementsLeft()-1);
    }
    
}

bool Zombie::isParalysed()
{
    return m_paralysed;
}

void Zombie::setParalysed(bool paralysis_state)
{
    m_paralysed = paralysis_state;
}

bool Zombie::isAlive()
{
    return m_alive;
}

void Zombie::setAlive(bool alive_state)
{
    m_alive = alive_state;
}

int Zombie::movementsLeft()
{
    return m_movementPlan;
}

void Zombie::newMovement(int moveNum)
{
    m_movementPlan = moveNum;
}
