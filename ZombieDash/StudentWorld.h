#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_


#include "GameWorld.h"
#include <vector>

#include <string>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Penelope;
class Actor;
class Citizen;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    void SetLevelCompleted (bool levelStatus);
    
    bool blockCheck(double dest_x,double dest_y,  Actor* thisActor) const;

    // Record that one more citizen on the current level is gone (exited,
    // died, or turned into a zombie).
    void recordCitizenGone(Citizen* c);
    
    // Indicate that the player has finished the level if all citizens
    // are gone.
    void recordLevelFinishedIfAllCitizensGone();
    
    bool noMoreCitizens();
    bool touching(Actor *a1, Actor *a2);
    
    Actor* getPenelopePointer();
    
private:
    void loadLevel();
    
    
    
    int m_nCitizens;
    vector<Actor*> actorVector;
    Penelope* penelopeptr;
    bool m_levelCompleted;
};  
 
#endif // STUDENTWORLD_H_
