#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"


class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject
{
public:
    Actor(int imgID, double x, double y, StudentWorld* sw, int dir, int depth);
    virtual ~Actor();
    
    virtual void doSomething() = 0;
    virtual bool canUseExitAndGetInfected();
    //Checks whether a proposed move by an actor is valid
    bool checkActorMove(double x, double y,  Actor* actorPassed);
    virtual void activateIfAppropriate(Actor* a);
    virtual void changeFlameCharges(int newCharges); //Only applicable for Penelope, for all other actors, nothing happens (so it is redefined more usefully in Penelope's class)
    
    virtual bool blocksMovement() const; // Does this object block agent movement?
    //virtual bool blocksFlame() const;
    virtual void dieByFallOrBurnIfAppropriate(); //Kills this actor where it is possible (i.e. agents)

    virtual bool canBeVomitedOn() const;
    
    StudentWorld* getWorld() const;
    virtual void infect(); //Infects an actor. This will only have an impact on those actors (humans) that can be infected. For all others, there is no action taken
    bool getInPlay();
    void setInPlay(bool status);
private:
    StudentWorld *swptr;
    bool m_inPlay; //Since I had already used 'alive' for another reason at this point, I decided to use 'inPlay' as my boolean to check if an object was validly in existence
};


class Agent : public Actor
{
public:
    Agent(int imageID, double x, double y, StudentWorld* sw, int dir);
    virtual bool blocksMovement() const;
    //virtual bool triggersOnlyActiveLandmines() const;
    void moveHelper(double x, double y, int dir, Actor* ap);
};



class ActivatingObject : public Actor
{
public:
    ActivatingObject(int imageID, double x, double y, StudentWorld* sw, int depth, int dir);
    int getTicks() const;
    void addTick();
private:
    int m_ticksLasted;
};

class Exit : public ActivatingObject
{
public:
    Exit(double x, double y, StudentWorld* sw);
    bool allowExit();
    virtual void doSomething();
    virtual void activateIfAppropriate(Actor* a);
    //virtual bool blocksFlame() const;
    
};

class Vomit : public ActivatingObject
{
public:
    Vomit(double x, double y, StudentWorld* sw, int dir);
    virtual void doSomething();
    virtual void activateIfAppropriate(Actor* a);
private:
    int m_ticksLasted;
};

class Human : public Agent
{
public:
    Human(int imageID, double x, double y, StudentWorld* sw);
    //virtual void beVomitedOnIfAppropriate();
    //virtual bool triggersZombieVomit() const;
    virtual bool canUseExitAndGetInfected();
    // Make this human uninfected by vomit.
    void clearInfection();
    virtual void infect();
    bool infected();
    void changeInfection(int newinf);
    virtual bool canBeVomitedOn() const;
    // How many ticks since this human was infected by vomit?
    int getInfectionDuration() const;
private:
    bool m_infectedStatus;
    int m_infectionCount;
};

class Citizen : public Human
{
public:
    Citizen(double x, double y, StudentWorld* sw);
    virtual void doSomething();
    virtual void dieByFallOrBurnIfAppropriate();
    bool isParalysed();
    
private:
    
    bool m_alive;
    bool m_paralysed;
};

class Wall: public Actor
{
public:
    Wall(double x, double y, StudentWorld* sw);
    virtual void doSomething();
    virtual ~Wall();
    virtual bool blocksMovement() const;
    
    
};

class Penelope: public Human
{
public:
    Penelope(double x, double y, StudentWorld* sw);
    virtual ~Penelope();
    virtual void doSomething();
    virtual void changeFlameCharges(int newCharges);
    int FlameCharges() const;
    void dieByFallOrBurnIfAppropriate();
    
private:
    void fireFlamethrower(int dir);
    int m_nFlameCharges;
    
    
    
};

class Goodie: public ActivatingObject
{
public:
    Goodie(int IID, double x, double y, StudentWorld* sw);
};

class GasCanGoodie: public Goodie
{
public:
    GasCanGoodie(double x, double y, StudentWorld* sw);
    void doSomething();
    virtual void activateIfAppropriate(Actor* a);
};

class Zombie : public Agent
{
public:
    Zombie(double x, double y, StudentWorld* sw);
    bool isParalysed(); //Checks if the zombie is paralysed on this tick
    void setParalysed(bool paralysis_state); //Changes the paralysis state of the zombie
    
    
    
    bool isAlive(); //Checks the zombie is alive
    void setAlive(bool alive_state);
    
    int movementsLeft(); //Returns the number of moves left in the current movement plan
    void newMovement(int moveNum); //Defines a new movement plan
    
protected:
    bool tryVomit(); //Tries to see if the zombie can vomit
    bool vomitProbability() const; //Returns whether a zombie should vomit from a 1/3 chance
    
private:
    
    bool m_paralysed;
    bool m_alive;
    int m_movementPlan;
};

class DumbZombie : public Zombie
{
public:
    DumbZombie(double x, double y, StudentWorld* sw);
    virtual void doSomething();
    virtual void dieByFallOrBurnIfAppropriate();
};

class SmartZombie : public Zombie
{
public:
    SmartZombie(double x, double y, StudentWorld* sw);
    virtual void doSomething();
    //virtual void dieByFallOrBurnIfAppropriate();
};


class Flame : public ActivatingObject
{
public:
    Flame(double x, double y, StudentWorld* sw, int dir);
    void doSomething();
    virtual void activateIfAppropriate(Actor* a);
};

#endif // ACTOR_H_
