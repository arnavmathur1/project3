


#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include "Actor.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;


int level = 1;

GameWorld* createStudentWorld(string assetPath)
{
    
    
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}  

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    
    int outcome = loadLevel();
    
if (outcome!=GWSTATUS_CONTINUE_GAME)
    return outcome;
    
    m_levelCompleted = false;
    m_levelFailed = false;
    return GWSTATUS_CONTINUE_GAME;
}

bool StudentWorld::touching(Actor *a1, Actor *a2)
{
    
    
    double dx = a1->getX() - a2->getX();
    double dy = a1->getY() - a2->getY();
    
    double distance = sqrt((dx*dx) + (dy*dy));
    if (distance <= 10)
    {
        return true;
    }
    
    return false;
}

void StudentWorld::flamethrowerActivated(double x, double y, int dir)
{
   
    Actor* actorptr = new Flame(x, y, this, dir);
    actorVector.push_back(actorptr);
    
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    
    
    
    
    if(m_levelFailed)
    {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    
    
    for (int a = 0; a<actorVector.size(); a++)
    {
        actorVector[a]->doSomething(); //Calls on each actor to do something
        activateOnAppropriateActors(actorVector[a]); //Activates any actors that may need activating
        
        
        if (actorVector[a]->canUseExitAndGetInfected())
        {
            if (actorVector[a] == penelopeptr) //If the actor can use the exit and is penelope, there are additional requirements that must be met before this can happen compared to other humans (i.e. there are no more citizens left in the level)
            {
                if (m_levelCompleted) //If the levelCompleted boolean has been flagged true, Penelope has met the requirements to exit and is at the exit, so the level has been completed
                {
                    
                    playSound(SOUND_LEVEL_FINISHED);
                    level++;
                    
                    return GWSTATUS_FINISHED_LEVEL;
                }
            }
            
            
        }
        if (!actorVector[a]->getInPlay())
        {
            delete actorVector[a];
            for (int i = 0; i<actorVector.size(); i++)
            {
                if (actorVector[i] == actorVector[a])
                {
                    actorVector.erase(actorVector.begin() + i);
                    break;
                }
            }
        }
        
        
    }
    
    ostringstream statbar;
    
    //... suppose some code here gives k the value 123
    statbar.fill('0');
    statbar<<"Score: "<<setw(6)<<getScore()<<"  "<<"Level: "<<getLevel()<<"  "<<"Lives: "<<getLives()<<"  "<<"Vaccines: "<<penelopeptr->Vaccines()<<"  "<<"Flames: "<<penelopeptr->FlameCharges()<<"  "<<"Mines: "<<penelopeptr->Landmines()<<"  "<<"Infected: "<<penelopeptr->getInfectionDuration();
    statbar.fill('0');
    string s = statbar.str();
    setGameStatText(s);
    
    return GWSTATUS_CONTINUE_GAME;
    
}

void StudentWorld::cleanUp()
{
    
    for (int i = 0; i<actorVector.size(); i++)
    {
        delete actorVector[i]; //Deallocates whatever each actor pointer points to
        
    }
    actorVector.clear(); //Empties the vector
    

    
    
}

int StudentWorld::loadLevel()
{
    m_nCitizens = 0;
    
    ostringstream oss;
    
    //... suppose some code here gives k the value 123
    oss.fill('0');
    oss<<"level" << setw(2) << level <<".txt";
    
    
    string s = oss.str();
    Level lev(assetPath());
    string levelFile = s;
    //string levelFile = "level06.txt";
    Level::LoadResult result = lev.loadLevel(levelFile); //loading the file
    
    if (result == Level::load_fail_bad_format)
        return GWSTATUS_LEVEL_ERROR;
    
    if (result == Level::load_fail_file_not_found)
        return GWSTATUS_PLAYER_WON;
    
    for (int y = 0; y<LEVEL_HEIGHT; y++) //Iterating through every coordinate within the maze
    {
        for(int x = 0; x<LEVEL_WIDTH; x++)
        {
            Level::MazeEntry xy = lev.getContentsOf(x,y);
            int true_x = x*SPRITE_WIDTH; //Setting the pixel-adjusted x and y coordinates
            int true_y = y*SPRITE_HEIGHT;
            Actor *actorptr;
            switch (xy)
            {
                case Level::player:
                    penelopeptr = new Penelope(true_x, true_y, this); //allocating a new Penelope for this level, passing a pointer to this studentWorld
                    
                    //penelopeptr = new Penelope(80, 80, this); //allocating a new Penelope for this level, passing a pointer to this studentWorld
                    
                    actorVector.push_back(penelopeptr); //Penelope too is an actor after all, thus should not be treated any differently and oushed into the vector
                    break;
                    
                case Level::wall:
                    actorptr = new Wall(true_x, true_y, this);
                    actorVector.push_back(actorptr); //Adds each new actor to the vector
                    break;
                    
                case Level::exit:
                    actorptr = new Exit(true_x, true_y, this);
                    actorVector.push_back(actorptr);
                    break;
                    
                case Level::citizen:
                    actorptr = new Citizen(true_x, true_y, this);
                    actorVector.push_back(actorptr);
                    m_nCitizens++;
                    break;
                    
                case Level::smart_zombie:
                    actorptr = new SmartZombie(true_x, true_y, this);
                    actorVector.push_back(actorptr);
                    break;
                    
                case Level::dumb_zombie:
                    actorptr = new DumbZombie(true_x, true_y, this);
                    actorVector.push_back(actorptr);
                    break;
                    
                case Level::gas_can_goodie:
                    actorptr = new GasCanGoodie(true_x, true_y, this);
                    actorVector.push_back(actorptr);
                    break;
                    
                case Level::pit:
                    actorptr = new Pit(true_x, true_y, this);
                    actorVector.push_back(actorptr);
                    break;
                    
                case Level::landmine_goodie:
                    actorptr = new LandmineGoodie(true_x, true_y, this);
                    actorVector.push_back(actorptr);
                    break;
                    
                case Level::vaccine_goodie:
                    actorptr = new VaccineGoodie(true_x, true_y, this);
                    actorVector.push_back(actorptr);
                    break;
                    
                case Level::empty:
                default:
                    break;
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}


bool StudentWorld::blockCheck(double dest_x, double dest_y, Actor* actorPassed) const
{
    
    
    double ARightX = dest_x+SPRITE_WIDTH-1; //TOP RIGHT CORNER coordinates of the object that requested the move (object A)
    double ARightY = dest_y+SPRITE_HEIGHT-1;
    
    bool blocked = false;
    ;
    
    for (int i = 0; i<actorVector.size(); i++)
    {
        Actor *thisActor = actorVector[i];
        
        
        
        double BRightX = thisActor->getX()+SPRITE_WIDTH-1; //TOP RIGHT CORNER coordinates of the object that could potentially block move (object B)
        double BRightY = thisActor->getY()+SPRITE_HEIGHT-1;
        
        
        if(thisActor == actorPassed) //We do not want to inhibit movement by blocking ourselves
            continue;
        
        //A condition that took me FOREVER to code but checks for overlaps at ANY of the 4 vertices of either object (basically some common area or shared edge prevents movement)
        
        if    ((ARightX>=thisActor->getX() && ARightY>=thisActor->getY() && ARightX<=BRightX && ARightY<=BRightY)
               || (BRightX>=dest_x && BRightY>=dest_y && BRightX<=ARightX && BRightY<=ARightY)
               || (ARightX>=thisActor->getX() && dest_x<=thisActor->getX() && dest_y>=thisActor->getY() && dest_y<=thisActor->getY()+SPRITE_HEIGHT-1)
               || (dest_x<=BRightX && dest_x>=thisActor->getX() && ARightY>=thisActor->getY() && ARightY<=BRightY))
            
            
        {
            
            if(thisActor->blocksMovement())
            {
                blocked = true;
                break;
                
            }
            
            if (!thisActor->blocksMovement()) //if the actor does not block movement, then the proposed move is valid
            {
                blocked = false;
                continue;
            }
            
            
            //return false;
            
            
        }
        
    }
    //return true;
    return !blocked;
}

bool StudentWorld::flameCheck(double dest_x, double dest_y, Actor* actorPassed) const
{
    
    
    double ARightX = dest_x+SPRITE_WIDTH-1; //TOP RIGHT CORNER coordinates of the object that requested the move (object A)
    double ARightY = dest_y+SPRITE_HEIGHT-1;
    
    bool blocked = false;
    ;
    
    for (int i = 0; i<actorVector.size(); i++)
    {
        Actor *thisActor = actorVector[i];
        
        
        
        double BRightX = thisActor->getX()+SPRITE_WIDTH-1; //TOP RIGHT CORNER coordinates of the object that could potentially block move (object B)
        double BRightY = thisActor->getY()+SPRITE_HEIGHT-1;
        
        
        if(thisActor == actorPassed) //We do not want to inhibit movement by blocking ourselves
            continue;
        
        //A condition that took me FOREVER to code but checks for overlaps at ANY of the 4 vertices of either object (basically some common area or shared edge prevents movement)
        
        if    ((ARightX>=thisActor->getX() && ARightY>=thisActor->getY() && ARightX<=BRightX && ARightY<=BRightY)
               || (BRightX>=dest_x && BRightY>=dest_y && BRightX<=ARightX && BRightY<=ARightY)
               || (ARightX>=thisActor->getX() && dest_x<=thisActor->getX() && dest_y>=thisActor->getY() && dest_y<=thisActor->getY()+SPRITE_HEIGHT-1)
               || (dest_x<=BRightX && dest_x>=thisActor->getX() && ARightY>=thisActor->getY() && ARightY<=BRightY))
            
            
        {
            
            if(thisActor->blocksFlame())
            {
                blocked = true;
                break;
                
            }
            
            if (!thisActor->blocksFlame()) //if the actor does not block movement, then the proposed move is valid
            {
                blocked = false;
                continue;
            }
            
            
            //return false;
            
            
        }
        
    }
    //return true;
    return !blocked;
}

void StudentWorld::recordCitizenInfectedOrDied(Actor* c, int typeOfDeath) //This is a nifty function because a citizen being infected and dying due to a flame have similar processes. Therefore, if the citizen is infected and turns into a zombie, I run the final 2 commands to create a new zombie (I check this by passing a 0 in homage to the movie motif of "patient zero." Otherwise we pass a 1 if the citizen has died due to a pit or a flame
{
    double c_x = c->getX();
    double c_y = c->getY();
    
    delete c;
    
    for (int i = 0; i<actorVector.size(); i++)
    {
        if (actorVector[i] == c)
        {
            actorVector.erase(actorVector.begin() + i);
            m_nCitizens--;
        }
    }
    increaseScore(-1000);
    if (typeOfDeath == 0)
    {
        int zombieprobs = randInt(1, 10);
        
        if(zombieprobs<=3)
        {
        
        Actor* actorptr = new SmartZombie(c_x, c_y, this);
        actorVector.push_back(actorptr);
        playSound(SOUND_ZOMBIE_BORN);
        }
        else
        {
            Actor* actorptr = new DumbZombie(c_x, c_y, this);
            actorVector.push_back(actorptr);
            playSound(SOUND_ZOMBIE_BORN);
        }
    }
    if(typeOfDeath == 1)
    {
        playSound(SOUND_CITIZEN_DIE);
    }
}

void StudentWorld::recordZombieDied(Actor *c, int typeOfZombie)
{
    if (c->hasVaccine())
    {
        double tempx = c->getX();
        double tempy = c->getY();
        
        int dir = randInt(0, 3);
        switch (dir)
        {
            case 0:
                if(c->checkActorMove(tempx+SPRITE_WIDTH, tempy, c))
                    new VaccineGoodie(tempx+SPRITE_WIDTH, tempy, this);
                break;
            case 1:
                if(c->checkActorMove(tempx-SPRITE_WIDTH, tempy, c))
                    new VaccineGoodie(tempx-SPRITE_WIDTH, tempy, this);
                break;
            case 3:
                if(c->checkActorMove(tempx, tempy -SPRITE_HEIGHT, c))
                    new VaccineGoodie(tempx, tempy -SPRITE_HEIGHT , this);
                break;
            case 2:
                if(c->checkActorMove(tempx, tempy +SPRITE_HEIGHT, c))
                    new VaccineGoodie(tempx, tempy + SPRITE_HEIGHT , this);
                break;
            default:
                break;
        }
    }
    playSound(SOUND_ZOMBIE_DIE);
    delete c;
    
    for (int i = 0; i<actorVector.size(); i++)
    {
        if (actorVector[i] == c)
        {
            actorVector.erase(actorVector.begin() + i);
            return;
        }
    }
    
    if (typeOfZombie == 0)
    {
        increaseScore(1000); //For a dumb zombie
        
    }
    if (typeOfZombie == 1)
        increaseScore(2000);
}

void StudentWorld::recordCitizenExit(Actor* c)
{
    delete c;
    increaseScore(500);
    playSound(SOUND_CITIZEN_SAVED);
    for (int i = 0; i<actorVector.size(); i++)
    {
        if (actorVector[i] == c)
        {
            actorVector.erase(actorVector.begin() + i);
            m_nCitizens--;
            return;
        }
    }
}

Actor* StudentWorld :: getPenelopePointer()
{
    return penelopeptr;
}

void StudentWorld::activateOnAppropriateActors(Actor* someActor)
{
    for (int i = 0; i<actorVector.size(); i++)
    {
        
        
        if (touching(actorVector[i], someActor))
        {
            if(someActor == actorVector[i])
            {
                continue;
            }
            actorVector[i]->activateIfAppropriate(someActor);
        }
    }
}

bool StudentWorld::noMoreCitizens()
{
    
    if (m_nCitizens == 0)
        return true;
    return false;
}

void StudentWorld::SetLevelCompleted(bool levelStatus)
{
    m_levelCompleted = true;
}

void StudentWorld::newLandmine(double x, double y)
{
    Actor* actorptr = new Landmine(x, y, this);
    actorVector.push_back(actorptr); //Adds each new actor to the vector
}

void StudentWorld::newPit(double x, double y)
{
    Actor* actorptr = new Pit(x, y, this);
    actorVector.push_back(actorptr); //Adds each new actor to the vector
}

bool StudentWorld::isZombieVomitTriggerAt(double x, double y) const
{
    
    for (int i = 0; i<actorVector.size(); i++)
    {
        
        double aX = actorVector[i]->getX();
        double aY = actorVector[i]->getY();
        
        if (x == aX && y == aY)
        {
            if (actorVector[i]->canBeVomitedOn())
                return true;
        }
        
    }
    
    return false;
    
}

void StudentWorld::newVomit(double x, double y, int dir)
{
    Actor* actorptr = new Vomit(x, y, this, dir);
    actorVector.push_back(actorptr); //Adds each new actor to the vector
    playSound(SOUND_ZOMBIE_VOMIT);
}

void StudentWorld::levelFailed(bool status)
{
    m_levelFailed = status;
}

Actor* StudentWorld::locateNearestVomitTrigger(double x, double y, double& otherX, double& otherY, double& distance)
{
    otherX = otherY = 256;
    
    double minD = 363;
    Actor* minActor = nullptr;
    for (int i = 0; i<actorVector.size(); i++)
    {
        if (!actorVector[i]->canUseExitAndGetInfected())
        {
            continue;
        }
        double dx = x - actorVector[i]->getX();
        double dy = y - actorVector[i]->getY();
        
        double d = sqrt((dx*dx) + (dy*dy));
        
        
        
        if (d<minD)
        {
            
            distance = d;
            otherX = actorVector[i]->getX();
            otherY = actorVector[i]->getY();
            minActor = actorVector[i];
        }
    }
    return minActor;
}
