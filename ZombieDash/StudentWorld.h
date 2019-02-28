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
    
    void SetLevelCompleted (bool levelStatus); //Allows the level to be completed
    
    bool blockCheck(double dest_x,double dest_y,  Actor* thisActor) const; //Checks if the propsed move has an actor that would block it
    bool flameCheck(double dest_x,double dest_y,  Actor* thisActor) const; //Checks if the propsed move has an actor that would block it

    void newVomit(double x, double y, int dir);
    
    // Record that one more citizen on the current level is gone (exited,
    // died, or turned into a zombie).
    void recordCitizenExit(Actor* c);
    void recordCitizenInfectedOrDied(Actor* c, int typeOfDeath);
    void recordZombieDied(Actor* c);
    void activateOnAppropriateActors(Actor* someActor); //Activates some function on an actor
    bool isZombieVomitTriggerAt(double x, double y) const; //Checks if there is a human at position (x,y) that can be vomited on
    void levelFailed (bool status); //Used to flag that Penelope has turned into a zombie (i.e. failed that level)
    // Indicate that the player has finished the level if all citizens
    // are gone.
    void recordLevelFinishedIfAllCitizensGone();
    
    void flamethrowerActivated(double x, double y, int dir);
    
    bool noMoreCitizens(); //Checks if there are any more citizens
    bool touching(Actor *a1, Actor *a2);
    
    Actor* getPenelopePointer();
    
private:
    void loadLevel();
    
    
    
    int m_nCitizens;
    vector<Actor*> actorVector;
    Penelope* penelopeptr;
    bool m_levelCompleted;
    bool m_levelFailed;
};  
 
#endif // STUDENTWORLD_H_
