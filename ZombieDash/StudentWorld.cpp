


#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include "Actor.h"

#include <string>
using namespace std;




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
    
    loadLevel();
    m_levelCompleted = false;
    return GWSTATUS_CONTINUE_GAME;
}

bool StudentWorld::touching(Actor *a1, Actor *a2)
{
    
    
    double dx = a1->getX() - a2->getX();
    double dy = a1->getY() - a2->getY();
    
    double distance = sqrt((dx*dx) + (dy*dy));
    //cout<<distance<<" ";
    if (distance <= 10)
    {
        return true;
    }
    
    return false;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    
    
    
    if(getLives() == 0)
        return GWSTATUS_PLAYER_DIED;
    
    for (int a = 0; a<actorVector.size(); a++)
    {
        actorVector[a]->doSomething();
        
        
        if (actorVector[a]->canUseExit())
        {
            if (actorVector[a] == penelopeptr)
            {
                if (m_levelCompleted)
                {
                    cout<<m_nCitizens;
                    cout<<"WE DONE";
                    playSound(SOUND_LEVEL_FINISHED);
                    return GWSTATUS_FINISHED_LEVEL;
                }
            }
            
            
        }
        
    }
    
    
    
    return GWSTATUS_CONTINUE_GAME;
    
}

void StudentWorld::cleanUp()
{
    
    for (int i = 0; i<actorVector.size(); i++)
    {
        delete actorVector[i]; //Deallocates whatever each actor pointer points to
        
    }
    actorVector.clear(); //Empties the vector
    
    if (actorVector.empty())
        cout<<"  Mission ACCOMPLISHED";
    
    
}

void StudentWorld::loadLevel()
{
    m_nCitizens = 0;
    
    Level lev(assetPath());
    string levelFile = "level02.txt";
    lev.loadLevel(levelFile); //loading the file
    
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
                    actorptr = new Wall(11, true_x, true_y, this);
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
                    cout<<m_nCitizens<<endl;
                    break;
                    
                case Level::smart_zombie:
                    actorptr = new SmartZombie(true_x, true_y, this);
                    actorVector.push_back(actorptr);
                    break;
                    
                case Level::dumb_zombie:
                    actorptr = new DumbZombie(true_x, true_y, this);
                    actorVector.push_back(actorptr);
                    break;
                    
                case Level::empty:
                default:
                    break;
            }
        }
    }
    
}


bool StudentWorld::blockCheck(double dest_x, double dest_y, Actor* actorPassed) const
{
    
    
    double ARightX = dest_x+SPRITE_WIDTH-1; //TOP RIGHT CORNER coordinates of the object that requested the move (object A)
    double ARightY = dest_y+SPRITE_HEIGHT-1;
    
    
    //cout<<"size: "<<actorVector.size()<<endl;
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
            
            if (!thisActor->blocksMovement()) //if the actor does not block movement, then the proposed move is valid
            {
                
                return true;
            }
            
            
            return false;
            
        }
        
    }
    return true;
}

void StudentWorld::recordCitizenGone(Citizen* c)
{
    delete c;
    
    for (int i = 0; i<actorVector.size(); i++)
    {
        if (actorVector[i] == c)
        {
            actorVector.erase(actorVector.begin() + i);
            return;
        }
    }
}

Actor* StudentWorld :: getPenelopePointer()
{
    return penelopeptr;
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
