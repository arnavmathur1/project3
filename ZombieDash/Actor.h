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
    
    virtual void doSomething(); 
    virtual bool canUseExit();
    //Checks whether a proposed move by an actor is valid
    bool checkActorMove(double x, double y,  Actor* actorPassed);
    
    // Does this object block agent movement?
    virtual bool blocksMovement() const;
    bool touching(Actor* a1, Actor* a2);

    
    StudentWorld* getWorld() const;
    
private:
    StudentWorld *swptr;
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
};

class Exit : public ActivatingObject
{
public:
    Exit(double x, double y, StudentWorld* sw);
    bool allowExit();
    virtual void doSomething();
    //virtual void activateIfAppropriate(Actor* a);
    //virtual bool blocksFlame() const;
  
};

class Human : public Agent
{
public:
    Human(int imageID, double x, double y, StudentWorld* sw);
    //virtual void beVomitedOnIfAppropriate();
    //virtual bool triggersZombieVomit() const;
    virtual bool canUseExit();
    // Make this human uninfected by vomit.
    void clearInfection();
    
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
    Wall(int imgID, int x, int y, StudentWorld* sw);
    //virtual void doSomething();
    virtual ~Wall();
    virtual bool blocksMovement() const;
    
    
};

class Penelope: public Human
{
public:
    Penelope(double x, double y, StudentWorld* sw);
    virtual ~Penelope();
    virtual void doSomething();
    
    
private:
    

    
};


class Zombie : public Agent
{
public:
    Zombie(StudentWorld* w,  double x, double y);
};

class DumbZombie : public Zombie
{
public:
    DumbZombie(StudentWorld* w,  double x, double y);
    virtual void doSomething();
    virtual void dieByFallOrBurnIfAppropriate();
};

class SmartZombie : public Zombie
{
public:
    SmartZombie(StudentWorld* w,  double x, double y);
    virtual void doSomething();
    virtual void dieByFallOrBurnIfAppropriate();
};

#endif // ACTOR_H_
