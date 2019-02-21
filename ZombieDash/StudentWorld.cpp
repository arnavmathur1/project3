


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
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    
    penelopeptr->doSomething();
    
    if(getLives() == 0)
        return GWSTATUS_PLAYER_DIED;
    
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
    
    /*for (int i = 0; i<actorVector.size(); i++)
        cout<<actorVector[i];*/
    
    //delete penelopeptr; //Deallocates the Penelope object
}

void StudentWorld::loadLevel() 
{
    Level lev(assetPath());
    string levelFile = "level01.txt";
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
                    penelopeptr = new Penelope(0, true_x, true_y, this); //allocating a new Penelope for this level, passing a pointer to this studentWorld
                    actorVector.push_back(penelopeptr); //Penelope too is an actor after all, thus should not be treated any differently and oushed into the vector
                    break;
                case Level::wall:
                    actorptr = new Wall(11, true_x, true_y, this);
                    actorVector.push_back(actorptr); //Adds each new actor to the vector
                    break;
                case Level::empty:
                default:
                    break; 
            }
        }
    }
    
}

int cunt = 0;

bool StudentWorld::blockCheck(double dest_x, double dest_y,  Actor* actorPassed) const
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
            
            //{
            cout<<dest_x<<", "<<dest_y<<"       actorx: "<<thisActor->getX()<<"         actory: "<<thisActor->getY()<<endl;
            cout<<"false";
            return false;
            //}
        }
        cunt=cunt+1;
        cout<<cunt<<endl;
    }
    return true;
}
