#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_


#include "GameWorld.h"
#include <vector>

#include <string>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Penelope;
class Actor;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    bool blockCheck(double dest_x,double dest_y,  Actor* thisActor) const;

private:
    void loadLevel() ;
    
    vector<Actor*> actorVector;
    Penelope* penelopeptr;
};  
 
#endif // STUDENTWORLD_H_
