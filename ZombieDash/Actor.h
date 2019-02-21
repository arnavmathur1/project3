#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"


class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject
{
public:
    Actor(int imgID, int x, int y, StudentWorld* sw);
    virtual ~Actor();
    
    virtual void doSomething();
    
    bool checkActorMove(double x, double y,  Actor* actorPassed);
    
    StudentWorld* getWorld() const;
    
private:
    StudentWorld *swptr;
};

class Wall: public Actor
{
public:
    Wall(int imgID, int x, int y, StudentWorld* sw);
    virtual ~Wall();
};

class Penelope: public Actor
{
public:
    Penelope(int imgID, int x, int y, StudentWorld* sw);
    virtual ~Penelope();
    virtual void doSomething();
    
private:

    bool m_infectedStatus = false;
    int m_infectionCount = 0;
    
};


#endif // ACTOR_H_
