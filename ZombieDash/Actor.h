#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"


class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject
{
public:
    Actor(int imgID, int x, int y);
    virtual ~Actor();
    
    virtual void doSomething();
    
};

class Wall: public Actor
{
public:
    Wall(int imgID, int x, int y);
    virtual ~Wall();
};

class Penelope: public Actor
{
public:
    Penelope(int imgID, int x, int y);
    virtual ~Penelope();
    virtual void doSomething(int dir);
    
private:
    bool m_infectedStatus = false;
    int m_infectionCount = 0;
    StudentWorld *swptr;
};


#endif // ACTOR_H_
