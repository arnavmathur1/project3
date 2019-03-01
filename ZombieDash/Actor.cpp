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

void Actor::changeLandmines(int newLandmines)
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

void Actor::changeVaccines(int newVaccines)
{
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
        setInPlay(false);
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
    setInPlay(false);
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
    m_nLandmines = 0;
    m_nFlameCharges = 0;
    m_nVaccines = 0;
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
                break;
                
            case KEY_PRESS_TAB:
                getWorld()->newLandmine(getX(), getY());
                
            case KEY_PRESS_ENTER:
                if(Vaccines()>0)
                {
                    clearInfection();
                    changeVaccines(Vaccines()-1);
                }
                break;
                
            default:
                break;
        }
        
    }
    
}

void Human::clearInfection()
{
    m_infectedStatus = false;
    m_infectionCount = 0;
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

bool Actor::hasVaccine()
{
    return false;
}

bool Actor::canExplode() const
{
    return false;
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
}

void Penelope::changeLandmines(int newLandmines)
{
    m_nLandmines = newLandmines;
}

void Penelope::changeVaccines(int newVaccines)
{
    m_nVaccines = newVaccines;
}

int Penelope::FlameCharges() const
{
    return m_nFlameCharges;
}

int Penelope::Landmines() const
{
    return m_nLandmines;
}

int Penelope::Vaccines() const
{
    return m_nVaccines;
}

void Penelope::dieByFallOrBurnIfAppropriate()
{
    if (getInPlay())
        getWorld()->levelFailed(true);
}

void Exit::activateIfAppropriate(Actor *a)
{
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
        return; //When a zombie is dead this immediately returns. no modifications are made
    
    
    if(!getInPlay())
        return;
    
    if (isParalysed())
    {
        setParalysed(false);
        return;
    }
    
    if(tryVomit())
        return;
    
    setParalysed(true); //Paralyses zombies every alternate tick in connjunction with the if statement above
    
    
    double closestHumanX, closestHumanY = LEVEL_WIDTH;
    double minD = 363; //sqrt(2*256^2) finds the max distance between 2 objects in this game
    
    Actor* a = getWorld()->locateNearestVomitTrigger(getX(), getY(), closestHumanX, closestHumanY, minD);
    
    
    
    
    if (movementsLeft() == 0)
    {
        
        newMovement(randInt(3, 10));
        if (minD>80)
        {
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
        else if (minD<=80) //Checking this d is <80 pixels
        {
            double dx = getX() - closestHumanX;
            double dy = getY() - closestHumanY;
            
            if (getX() == a->getX() && dy<0)
            {
                /*
                 setDirection(up);
                 if(checkActorMove(getX(), getY()+1, this)) JUNK CODE IGNORE PLS
                 moveTo(getX(), getY()+1);
                 */
                setDirection(up);
                return;
            }
            else if (getX() == a->getX() && dy>0)
            {
                setDirection(down);
                //moveHelper(getX(), getY()-1, down, this);
                /*setDirection(down);
                 
                 if(checkActorMove(getX(), getY()-1, this))
                 moveTo(getX(), getY()-1);*/
                return;
            }
            
            
            else if (getY() == a->getY() && dx<0)
            {
                /*
                 setDirection(right);
                 if(checkActorMove(getX()+1, getY(), this))
                 moveTo(getX()+1, getY());*/
                //moveHelper(getX()+1, getY(), right, this);
                setDirection(right);
                return;
            }
            else if (getY() == a->getY() && dx>0)
            {
                /*
                 setDirection(left);
                 if(checkActorMove(getX()-1, getY(), this))
                 moveTo(getX()-1, getY());*/
                //moveHelper(getX()-1, getY(), left, this);
                setDirection(left);
                return;
            }
            
            else if (dy<0 && dx<0) //We now check each direction sequentially for the most appropriate citizen move based on its and Penelope's current position
            {
                int result = randInt(0, 1);
                
                if (result == 0) //Checking if up is valid
                {
                    if(checkActorMove(getX(), getY()+1, this))
                    {
                        setDirection(up);
                    }
                }
                else if (checkActorMove(getX()+1, getY(), this))
                {
                    setDirection(right);
                }
                return;
                
            }
            
            
            else if (dy>0 && dx<0)
            {
                int result = randInt(0, 1);
                
                if (result == 0)
                {
                    if(checkActorMove(getX(), getY()-1, this))
                    {
                        setDirection(down);
                    }
                }
                else if (checkActorMove(getX()+1, getY(), this))
                {
                    setDirection(right);
                }
                return;
                
            }
            
            else if (dy<0 && dx>0)
            {
                int result = randInt(0, 1);
                
                if (result == 0) //Checking if up is valid
                {
                    if(checkActorMove(getX(), getY()+1, this))
                    {
                        setDirection(up);
                    }
                }
                else if (checkActorMove(getX()-1, getY(), this))
                {
                    setDirection(left);
                }
                return;
                
            }
            
            else if (dy>0 && dx>0)
            {
                int result = randInt(0, 1);
                
                if (result == 0) //Checking if up is valid
                {
                    if(checkActorMove(getX(), getY()-1, this))
                    {
                        setDirection(down);
                    }
                }
                else if (checkActorMove(getX()-1, getY(), this))
                {
                    setDirection(left);
                }
                return;
            }
            
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
        {
            newMovement(movementsLeft()-1);
        }
    }
}





DumbZombie::DumbZombie(double x, double y, StudentWorld* sw):Zombie(x,y,sw)
{
    int q = randInt(1, 10);
    if (q == 1)
        m_hasVaccine = true;
    m_hasVaccine = false;
}



void DumbZombie::doSomething()
{
    if(!getInPlay())
        return;
    
    
    
    if (!isAlive())
        return; //When a citizen is dead this immediately returns. no modifications are made
    
    if (isParalysed())
    {
        setParalysed(false);
        return;
    }
    
    if(tryVomit())
        return;
    
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

bool DumbZombie::hasVaccine()
{
    return m_hasVaccine;
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
    setInPlay(false);
    if (getInPlay())
        getWorld()->recordZombieDied(this, 0);
}

void SmartZombie::dieByFallOrBurnIfAppropriate()
{
    setInPlay(false);
    
    if (getInPlay())
        getWorld()->recordZombieDied(this, 1);
}
//VOMIT

Vomit::Vomit(double x, double y, StudentWorld* sw, int dir):ActivatingObject(IID_VOMIT, x, y, sw, dir, 0)
{
    //m_ticksLasted = 0;
}

void Vomit::doSomething()
{
    if (!getInPlay())
        return;
    
    if (getTicks() == 2)
    {
        setInPlay(false);
    }
    
    
    addTick();
}



void Vomit::activateIfAppropriate(Actor *a)
{
    if (!getInPlay())
        return;
    if (a->canUseExitAndGetInfected())
    {
        a->infect();
    }
}

//Goodie

Goodie::Goodie(int IID, double x, double y, StudentWorld* sw):ActivatingObject(IID, x, y, sw, right, 1)
{
}

GasCanGoodie::GasCanGoodie(double x, double y, StudentWorld* sw):Goodie(IID_GAS_CAN_GOODIE, x, y, sw)
{
}

//GasCanGoodie

void GasCanGoodie::doSomething()
{
    if (!getInPlay())
        return;
}

void GasCanGoodie::activateIfAppropriate(Actor* a)
{
    if (!getInPlay())
        return;
    if (!a->getInPlay())
        return;
    if (a == getWorld()->getPenelopePointer())
    {
        getWorld()->increaseScore(50);
        setInPlay(false);
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->getPenelopePointer()->changeFlameCharges(5);
    }
}

void GasCanGoodie::dieByFallOrBurnIfAppropriate()
{
    setInPlay(false);
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
    if (!getInPlay())
        return;
    
    if (!a->getInPlay())
        return;
    
    if (a->canExplode())
        a->activateIfAppropriate(this);
    
    a->dieByFallOrBurnIfAppropriate();
}

//Vaccine Goodie
VaccineGoodie::VaccineGoodie(double x, double y, StudentWorld* sw):Goodie(IID_VACCINE_GOODIE, x, y, sw)
{
}

void VaccineGoodie::doSomething()
{
    if (!getInPlay())
        return;
}

void VaccineGoodie::activateIfAppropriate(Actor *a)
{
    if (a == getWorld()->getPenelopePointer())
    {
        getWorld()->increaseScore(50);
        setInPlay(false);
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->getPenelopePointer()->changeVaccines(1);
        
    }
}

//Landmine Goodie

LandmineGoodie::LandmineGoodie(double x, double y, StudentWorld* sw):Goodie(IID_LANDMINE_GOODIE, x, y, sw)
{
}


void LandmineGoodie::doSomething()
{
    if (!getInPlay())
        return;
}


void LandmineGoodie::activateIfAppropriate(Actor *a)
{
    if (!a->getInPlay())
        return;
    
    if (!getInPlay())
        return;
    
    if (a == getWorld()->getPenelopePointer())
    {
        getWorld()->increaseScore(50);
        setInPlay(false);
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->getPenelopePointer()->changeLandmines(2);
    }
}

void LandmineGoodie::dieByFallOrBurnIfAppropriate()
{
    setInPlay(false);
}

//PIT

Pit::Pit(double x, double y, StudentWorld* sw) : ActivatingObject(IID_PIT, x, y, sw, right, 0)
{
}

void Pit::doSomething()
{
    if (!getInPlay())
        return;
    
}

void Pit::activateIfAppropriate(Actor *a)
{
    if (!a->getInPlay())
        return;
    
    a->dieByFallOrBurnIfAppropriate();
    
}

//LANDMINE

Landmine::Landmine(double x, double y, StudentWorld* sw) : ActivatingObject(IID_LANDMINE, x, y, sw, right, 1)
{
    m_active = false;
}

bool Landmine::isActive()
{
    return m_active;
}

void Landmine::doSomething()
{
    if(!getInPlay())
        return;
    if (getTicks()==30)
    {
        m_active = true; //Activate Landmine after 30 ticks
        return;
    }
    
    addTick();
}

bool Landmine::canExplode() const
{
    return true;
}

void Landmine::activateIfAppropriate(Actor *a)
{
    if (!a->getInPlay())
        return;
    if (isActive())
    {
        setInPlay(false);
        getWorld()->playSound(SOUND_LANDMINE_EXPLODE);
        
        if (getWorld()->flameCheck(getX() , getY(), this))
        {
            getWorld()->flamethrowerActivated(getX() , getY(), up); //Current Point
        }
        
        if (getWorld()->flameCheck(getX() - SPRITE_WIDTH, getY(), this)) //left
        {
            getWorld()->flamethrowerActivated(getX() - SPRITE_WIDTH, getY(), up);
        }
        
        if (getWorld()->flameCheck(getX() + SPRITE_WIDTH, getY(), this)) //right
        {
            getWorld()->flamethrowerActivated(getX() + SPRITE_WIDTH, getY(), up);
        }
        
        if (getWorld()->flameCheck(getX() , getY()+ SPRITE_HEIGHT, this)) //up
        {
            getWorld()->flamethrowerActivated(getX() , getY()+ SPRITE_HEIGHT, up);
        }
        
        if (getWorld()->flameCheck(getX(), getY()- SPRITE_HEIGHT, this)) //down
        {
            getWorld()->flamethrowerActivated(getX() , getY()- SPRITE_HEIGHT, up);
        }
        
        if (getWorld()->flameCheck(getX() + SPRITE_WIDTH, getY()+ SPRITE_HEIGHT, this)) //NW
        {
            getWorld()->flamethrowerActivated(getX() + SPRITE_WIDTH, getY()+ SPRITE_HEIGHT, up);
        }
        
        if (getWorld()->flameCheck(getX() - SPRITE_WIDTH, getY() + SPRITE_HEIGHT, this)) //NE
        {
            getWorld()->flamethrowerActivated(getX() - SPRITE_WIDTH, getY() + SPRITE_HEIGHT, up);
        }
        
        if (getWorld()->flameCheck(getX() + SPRITE_WIDTH, getY()- SPRITE_HEIGHT, this)) //SW
        {
            getWorld()->flamethrowerActivated(getX() + SPRITE_WIDTH, getY()- SPRITE_HEIGHT, up);
        }
        
        if (getWorld()->flameCheck(getX() - SPRITE_WIDTH, getY()- SPRITE_HEIGHT, this)) //SW
        {
            getWorld()->flamethrowerActivated(getX() - SPRITE_WIDTH, getY() - SPRITE_HEIGHT, up);
        }
        
        //Introducing a new pit
        getWorld()->newPit(getX(), getY());
        
    }
}
