


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
    int x = 0;
    getKey(x);
    if (x == KEY_PRESS_UP)
    {
        cout<<"OK";
        decLives();
    }
    if(getLives() == 0)
        return GWSTATUS_PLAYER_DIED;
    
    return GWSTATUS_CONTINUE_GAME;
    
}

void StudentWorld::cleanUp()
{
    for (int i = 0; i<actorVector.size(); i++)
    {
        delete actorVector[i];
        
    }
    actorVector.clear();
    
    if (actorVector.empty())
        cout<<"Mission ACCOMPLISHED";
    
    /*for (int i = 0; i<actorVector.size(); i++)
        cout<<actorVector[i];*/
    
    delete penelopeptr;
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
            int true_y = y*SPRITE_WIDTH;
            Actor *actorptr;
            switch (xy)
            {
                case Level::player:
                    new Penelope(0, true_x, true_y); //allocating a new Penelope for this level
                    break;
                case Level::wall:
                    actorptr = new Wall(11, true_x, true_y);
                    actorVector.push_back(actorptr);
                    break;
                case Level::empty:
                default:
                    break;
            }
        }
    }
    
  
}
