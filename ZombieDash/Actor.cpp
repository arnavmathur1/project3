#include "Actor.h"
#include "StudentWorld.h"
#include "GameWorld.h"
#include "GameConstants.h"

#include <iostream>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imgID, double x, double y, StudentWorld* sw, int dir, int depth):GraphObject(imgID, x, y)
{
    
    swptr = sw;
    m_inPlay = true;
}
Actor::~Actor()
{
    
}

bool Actor::getInPlay()
{
    return m_inPlay;
}

void Actor::changeFlameCharges(int newCharges)
{}

void Actor::setInPlay(bool status)
{
    m_inPlay = status;
}

bool Actor::canBeVomitedOn() const
{
    return false;
}

void Actor::doSomething()
{
    
}

bool Actor::blocksFlame() const
{
    return false;
}

bool Exit::blocksFlame() const
{
    return true;
}

bool Wall::blocksFlame() const
{
    return true;
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

void Wall::doSomething()
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

ActivatingObject::ActivatingObject(int imageID, double x, double y, StudentWorld* sw, int direction, int depth): Actor (imageID, x, y, sw, direction, depth)
{
    m_ticksLasted = 0;
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
    
    
    if(getInfectionDuration() >= 500)
    {
        getWorld()->recordCitizenInfectedOrDied(this, 0);
        getWorld()->playSound(SOUND_ZOMBIE_BORN);
        return;
    }
    
    if(infected())
    {
        changeInfection(getInfectionDuration() + 1);
    }
    
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
                moveHelper(getX()-2, getY(), left, this);
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



void Human::changeInfection(int newinf)
{
    m_infectionCount = newinf;
}

void Agent::moveHelper(double x, double y,int dir, Actor *ap)
{
    setDirection(dir); //A movement function that can handle Agent movemennt
    if(checkActorMove(x, y, this))
        moveTo(x, y);
}

void Actor::infect()
{
}

void Human::infect()
{
    m_infectedStatus = true;
}

void Citizen::infect()
{
    Human::infect();
    getWorld()->playSound(SOUND_CITIZEN_INFECTED);
}

void Citizen::dieByFallOrBurnIfAppropriate()
{
    getWorld()->recordCitizenInfectedOrDied(this, 1);
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

int ActivatingObject::getTicks() const
{
    return m_ticksLasted;
}

void ActivatingObject::addTick()
{
    m_ticksLasted++;
}

bool Human::infected()
{
    return m_infectedStatus;
}

bool Human::canBeVomitedOn() const
{
    return true;
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
    
    if(getInfectionDuration() >= 500)
    {
        setInPlay(false);
        getWorld()->levelFailed(true);
        getWorld()->playSound(SOUND_PLAYER_DIE);
    }
    
    if(infected())
    {
        changeInfection(getInfectionDuration() + 1);
    }
    
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
            case KEY_PRESS_SPACE:
                fireFlamethrower(getDirection());
            default:
                break;
        }
        
    }
    
}

void Penelope::fireFlamethrower(int dir)
{
    if (FlameCharges()>0)
    {
        getWorld()->playSound(SOUND_PLAYER_FIRE);
        switch (dir)
        {
            case left:
                for (int i = 1; i<=3; i++)
                {
                    if (getWorld()->flameCheck(getX() - (i *SPRITE_WIDTH), getY(), this))
                    {
                        getWorld()->flamethrowerActivated(getX() - (i *SPRITE_WIDTH), getY(), left);
                    }
                    else
                        break;
                }
                changeFlameCharges(FlameCharges()-1);
                break;
                
            case right:
                for (int i = 1; i<=3; i++)
                {
                    if (getWorld()->flameCheck(getX() + (i *SPRITE_WIDTH), getY(), this))
                    {
                        getWorld()->flamethrowerActivated(getX() + (i *SPRITE_WIDTH), getY(), right);
                    }
                    else
                        break;
                }
                changeFlameCharges(FlameCharges()-1);
                break;
            case up:
                for (int i = 1; i<=3; i++)
                {
                    if (getWorld()->flameCheck(getX(), getY()+ (i *SPRITE_WIDTH), this))
                    {
                        getWorld()->flamethrowerActivated(getX() , getY() + (i *SPRITE_WIDTH), up);
                    }
                    else
                        break;
                }
                changeFlameCharges(FlameCharges()-1);
                break;
            case down:
                for (int i = 1; i<=3; i++)
                {
                    if (getWorld()->flameCheck(getX(), getY() - (i *SPRITE_WIDTH), this))
                    {
                        getWorld()->flamethrowerActivated(getX() , getY() - (i *SPRITE_WIDTH), down);
                    }
                    else
                        break;
                }
                changeFlameCharges(FlameCharges()-1);
                break;
        }
    }
}

Wall::Wall(double x, double y, StudentWorld* sw): Actor(IID_WALL, x, y, sw, right, 0)
{
    
}

void Exit::doSomething()
{
    /*
     studentworld is there something on top of me
     
     if yes, tell it that it is on top of an exit
     */
}

bool Actor::canUseExitAndGetInfected()
{
    return false;
}


bool Human::canUseExitAndGetInfected()
{
    return true;
}

int Human::getInfectionDuration() const
{
    return m_infectionCount;
}

Wall::~Wall()
{
    
}

void Actor::activateIfAppropriate(Actor *a)
{
    
}

void Actor::dieByFallOrBurnIfAppropriate()
{
}

void Penelope::changeFlameCharges(int newCharges)
{
    m_nFlameCharges = newCharges;
    cout<<"fc added";
}

int Penelope::FlameCharges() const
{
    return m_nFlameCharges;
}

void Penelope::dieByFallOrBurnIfAppropriate()
{
    getWorld()->levelFailed(true);
}

void Exit::activateIfAppropriate(Actor *a)
{
    //cout<<"Its being called";
    StudentWorld* sw = getWorld(); //Creates a new pointer to the student world
    /*if (getWorld()->touching(this, sw->getPenelopePointer())) //Checks if the wall and penelope are touching
     {
     if (sw->noMoreCitizens()) //When we are out of citizens (i.e. all safe/dead) the level has been completed and the exit functionality can be activated
     sw->SetLevelCompleted(true);
     }*/
    if (a == getWorld()->getPenelopePointer())
    {
        if (sw->noMoreCitizens()) //When we are out of citizens (i.e. all safe/dead) the level has been completed and the exit functionality can be activated
            sw->SetLevelCompleted(true);
    }
    else if (a->canUseExitAndGetInfected())
    {
        sw->recordCitizenExit(a);
        cout<<"YEEEEEEET";
    }
    
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

void SmartZombie::doSomething()
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

DumbZombie::DumbZombie(double x, double y, StudentWorld* sw):Zombie(x,y,sw)
{}

void DumbZombie::doSomething()
{
    if(tryVomit())
        return;
    
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
    }}

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

bool Zombie::vomitProbability() const
{
    int random = randInt(0, 2);
    
    if (random == 0)
        return true;
    return false;
}

bool Zombie::tryVomit()
{
    switch (getDirection())
    {
        case right:
            if (getWorld()->isZombieVomitTriggerAt(getX() + SPRITE_WIDTH, getY()))
            {
                getWorld()->newVomit(getX() + SPRITE_WIDTH, getY(), right);
                return true;
            }
        case left:
            if (getWorld()->isZombieVomitTriggerAt(getX() - SPRITE_WIDTH, getY()))
            {
                getWorld()->newVomit(getX() - SPRITE_WIDTH, getY(), left);
                return true;
            }
        case up:
            if (getWorld()->isZombieVomitTriggerAt(getX(), getY() + SPRITE_WIDTH))
            {
                
                getWorld()->newVomit(getX(), getY() + SPRITE_WIDTH, up);
                return true;
            }
        case down:
            if (getWorld()->isZombieVomitTriggerAt(getX(), getY() - SPRITE_WIDTH))
            {
                getWorld()->newVomit(getX(), getY() - SPRITE_WIDTH, down);
                return true;
            }
        default:
            break;
    }
    return false;
}

void DumbZombie::dieByFallOrBurnIfAppropriate()
{
    cout<<"@ME DEAD AF";
    getWorld()->recordZombieDied(this);
}

//VOMIT

Vomit::Vomit(double x, double y, StudentWorld* sw, int dir):ActivatingObject(IID_VOMIT, x, y, sw, dir, 0)
{
    //m_ticksLasted = 0;
}

void Vomit::doSomething()
{
    if (getTicks() == 2)
    {
        setInPlay(false);
    }
    
    
    addTick();
}



void Vomit::activateIfAppropriate(Actor *a)
{
    if (a->canUseExitAndGetInfected())
    {
        a->infect();
    }
}

//Goodies

Goodie::Goodie(int IID, double x, double y, StudentWorld* sw):ActivatingObject(IID, x, y, sw, right, 1)
{
}

GasCanGoodie::GasCanGoodie(double x, double y, StudentWorld* sw):Goodie(IID_GAS_CAN_GOODIE, x, y, sw)
{
}

void GasCanGoodie::doSomething()
{
}

void GasCanGoodie::activateIfAppropriate(Actor* a)
{
    if (a == getWorld()->getPenelopePointer())
    {
        setInPlay(false);
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->getPenelopePointer()->changeFlameCharges(5);
    }
}
//Flame

Flame::Flame(double x, double y, StudentWorld* sw, int dir):ActivatingObject(IID_FLAME, x, y, sw, dir, 0)
{
    
}

void Flame::doSomething()
{
    if(getTicks() == 2)
    {
        setInPlay(false);
    }
    
    addTick();
}

void Flame::activateIfAppropriate(Actor *a)
{
    a->dieByFallOrBurnIfAppropriate();
}

//Landmine Goodie

LandmineGoodie::LandmineGoodie(double x, double y, StudentWorld* sw):Goodie(IID_LANDMINE_GOODIE, x, y, sw)
{
}

void LandmineGoodie::doSomething()
{}

void LandmineGoodie::activateIfAppropriate(Actor *a)
{
    if (a == getWorld()->getPenelopePointer())
    {
        setInPlay(false);
        getWorld()->playSound(SOUND_GOT_GOODIE);
        //getWorld()->getPenelopePointer()->changeLandmines(2);
    }
}

 //PIT

Pit::Pit(double x, double y, StudentWorld* sw) : ActivatingObject(IID_PIT, x, y, sw, right, 0)
{
}

void Pit::doSomething()
{}

void Pit::activateIfAppropriate(Actor *a)
{
    a->dieByFallOrBurnIfAppropriate();
}

