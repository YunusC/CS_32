#include "StudentWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include <string>
#include "Level.h"
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), m_levelComplete(false), m_levelFailed(false), m_numOfCitizens(0), m_levelNum('1')
{
}

int StudentWorld::init()
{
    Object* newObject;
    for(int x = 0;x < LEVEL_WIDTH;x++)
    {
        for(int y = 0;y < LEVEL_HEIGHT;y++)
        {
            newObject = level(x,y);
            if(newObject != nullptr)
            {
                m_objects.insert(newObject);
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    if(m_levelFailed == true)
    {
        decLives();
        m_levelFailed = false;
        return GWSTATUS_PLAYER_DIED;
    }
    if(m_levelComplete == true)
    {
        m_levelNum++;
        m_levelComplete = false;
        playSound(SOUND_LEVEL_FINISHED);
        return GWSTATUS_FINISHED_LEVEL;
    }
    getKey(m_key);
    m_p->doSomething(m_key);
    m_key = -1;
    m_currObject = m_objects.begin();
    while(m_currObject != m_objects.end())
    {
        (*m_currObject)->doSomething();
        m_currObject++;
    }
    m_currObject = m_objects.begin();
    while(m_currObject != m_objects.end())
    {
        if(!(*m_currObject)->exists())
        {
            delete *m_currObject;
            m_objects.erase(m_currObject);
            m_currObject = m_objects.begin();
        }
        else
            m_currObject++;
    }
    m_gameStatStream.str("");
    m_gameStatStream.clear();
    m_gameStatStream << "Score: ";
    m_gameStatStream.fill('0');
    m_gameStatStream << setw(6) << getScore() << "  Level:";
    m_gameStatStream.fill(' ');
    m_gameStatStream << setw(3) << m_levelNum << "  Lives:" << setw(3) << getLives();
    m_gameStatStream << "   Vacc:" << setw(3) << m_p->numOfVaccines();
    m_gameStatStream << "   Flames:" << setw(3) << m_p->numOfFlames();
    m_gameStatStream << "   Mines:" << setw(3) << m_p->numOfLandmines();
    m_gameStatStream << "   Infected:" << setw(3) << m_p->infectionCount();
    m_gameStats = "";
    setGameStatText("");
    m_gameStats = m_gameStatStream.str();
    cout << m_gameStats << endl;
    setGameStatText(m_gameStats);
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    if(m_p == nullptr && m_currObject == m_objects.end())
        return;
    delete m_p;
    m_p = nullptr;
    m_currObject = m_objects.begin();
    while(!m_objects.empty() && m_currObject != m_objects.end())
    {
        delete (*m_currObject);
        m_objects.erase(m_currObject);
        m_currObject = m_objects.begin();
    }
}

Object* StudentWorld::level(int x, int y)
{
    Level lev(assetPath());
    string a;
    a += m_levelNum;
    string levelFile = "level0"+a+".txt";
    Level::LoadResult result = lev.loadLevel(levelFile);
    if (result == Level::load_fail_file_not_found)
        cerr << "Cannot find level0"+a+".txt data file" << endl;
    else if (result == Level::load_fail_bad_format)
        cerr << "Your level was improperly formatted" << endl;
    else if (result == Level::load_success)
    {
        cerr << "Successfully loaded level" << endl;
        Level::MazeEntry ge = lev.getContentsOf(x,y); // level_x=5, level_y=10
        switch (ge) // so x=80 and y=160
        {
            case Level::empty:
                break;
            case Level::smart_zombie:
                return new smartZombies(IID_ZOMBIE,x*SPRITE_WIDTH,y*SPRITE_HEIGHT,0,0,0,this);
                break;
            case Level::dumb_zombie:
                return new dumbZombies(IID_ZOMBIE,x*SPRITE_WIDTH,y*SPRITE_HEIGHT,0,0,0,this);
                break;
            case Level::player:
                m_p = new Penelope(IID_PLAYER,x*SPRITE_WIDTH,y*SPRITE_HEIGHT,0,0,0,this);
                break;
            case Level::exit:
                return new Exit(IID_EXIT,x*SPRITE_WIDTH,y*SPRITE_HEIGHT,0,1,0,this);
                break;
            case Level::wall:
                return new Wall(IID_WALL,x*SPRITE_WIDTH,y*SPRITE_HEIGHT,0,0,0,this);
                break;
            case Level::pit:
                return new Pit(IID_PIT,x*SPRITE_WIDTH,y*SPRITE_HEIGHT,0,0,0,this);
                break;
            case Level::citizen:
                m_numOfCitizens++;
                return new Citizens(IID_CITIZEN,x*SPRITE_WIDTH,y*SPRITE_HEIGHT,0,0,0,this);
                break;
            case Level::landmine_goodie:
                return new Landmines(IID_LANDMINE_GOODIE,x*SPRITE_WIDTH,y*SPRITE_HEIGHT,0,0,0,this);
                break;
            case Level::vaccine_goodie:
                return new Vaccines(IID_VACCINE_GOODIE,x*SPRITE_WIDTH,y*SPRITE_HEIGHT,0,0,0,this);
                break;
            case Level::gas_can_goodie:
                return new Gas(IID_GAS_CAN_GOODIE,x*SPRITE_WIDTH,y*SPRITE_HEIGHT,0,0,0,this);
                break;
                // etc…
        }
    }
    return nullptr;
}

//excellent way to destroy objects
void StudentWorld::destroy(Object* x)
{
    m_currObject = m_objects.find(x);
    if(m_currObject == m_objects.end())
        return;
    delete *m_currObject;
    m_objects.erase(m_currObject);
}

bool StudentWorld::blockMovement(double x1, double y1, Object* a, Object* b)
{
    if(a == b)
    {
        return false;
    }
    double x = (x1 - b->getX());
    double y = (y1 - b->getY());
    if(x < 0)
        x = -x;
    if(y < 0)
        y = -y;
    if((x < 16 && y < 16) && !b->canMoveThrough())
        return true;
    return false;
}

bool StudentWorld::determineIntersecting(Object* x, double a, double b)
{
    set<Object*>::iterator i;
    i = m_objects.begin();
    while(i != m_objects.end())
    {
        if(blockMovement(a, b, x, *i))
            return true;
        i++;
    }
    if(blockMovement(a,b,x, m_p))
        return true;
    return false;
}

bool StudentWorld::overlap(double x, double y, Object* a, Object* b)
{
    if(a == b)
        return false;
    double deltaX;
    double deltaY;
    deltaX = (a->getX() + x - b->getX())*(a->getX() + x - b->getX());
    deltaY = (a->getY() + y - b->getY())*(a->getY() + y - b->getY());
    if(deltaX + deltaY <= 100)
        return true;
    return false;
}

void StudentWorld::killOverlap(Object* a)
{
    set<Object*>::iterator i;
    i = m_objects.begin();
    while(i != m_objects.end())
    {
        if(overlap(0,0,a,*i) && (*i)->canDie())
            (*i)->destroy();
        i++;
    }
}

void StudentWorld::saveOverlap(Object* a)
{
    set<Object*>::iterator i;
    i = m_objects.begin();
    while(i != m_objects.end())
    {
        if(overlap(0,0,a,*i) && (*i)->canBeSaved())
            (*i)->save();
        i++;
    }
}

void StudentWorld::infectOverlap(Object* a)
{
    set<Object*>::iterator i;
    i = m_objects.begin();
    while(i != m_objects.end())
    {
        if(overlap(0,0,a,*i) && (*i)->canBeInfected())
            (*i)->infect();
        i++;
    }
}

bool StudentWorld::isOverlapping(Object* a)
{
    set<Object*>::iterator x;
    x = m_objects.begin();
    while(x != m_objects.end())
    {
        if(overlap(0,0,a,*x) && (*x)->canOverlap())
            return true;
        else
            x++;
    }
    return false;
}

void StudentWorld::createFlames(Object* a, Direction dir)
{
    int i = 1;
    set<Object*>::iterator x;
    while(i < 4)
    {
        x = m_objects.begin();
        if(x == m_objects.end())
            return;
        while(x != m_objects.end())
        {
        switch(dir)
        {
            case Character::up:
                if(overlap(0,i*SPRITE_HEIGHT,a,*x) && !(*x)->canOverlap())
                    return;
                break;
            case Character::down:
                if(overlap(0,-(i*SPRITE_HEIGHT),a,*x) && !(*x)->canOverlap())
                    return;
                break;
            case Character::left:
                if(overlap(-(i*SPRITE_WIDTH),0,a,*x) && !(*x)->canOverlap())
                    return;
                break;
            case Character::right:
                if(overlap(i*SPRITE_WIDTH,0,a,*x) && !(*x)->canOverlap())
                    return;
                break;
        }
            x++;
        }
        switch(dir)
        {
            case Character::up:
                m_objects.insert(new Flames(IID_FLAME,a->getX(),a->getY()+i*SPRITE_HEIGHT,0,0,0,this));
                break;
            case Character::down:
                m_objects.insert(new Flames(IID_FLAME,a->getX(),a->getY()-i*SPRITE_HEIGHT,0,0,0,this));
                break;
            case Character::left:
                m_objects.insert(new Flames(IID_FLAME,a->getX()-i*SPRITE_WIDTH,a->getY(),0,0,0,this));
                break;
            case Character::right:
                m_objects.insert(new Flames(IID_FLAME,a->getX()+i*SPRITE_WIDTH,a->getY(),0,0,0,this));
                break;
        }
        i++;
    }
}

void StudentWorld::activateLandmine(Object* a)
{
    set<Object*>::iterator x;
    x = m_objects.begin();
    if(x == m_objects.end())
        return;
    for(int i = -1;i < 2;i++)
        for(int j= -1;j < 2;j++)
        {
            while(x != m_objects.end())
            {
                if(overlap(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,a,*x) && !(*x)->canOverlap())
                    break;
                else
                    x++;
            }
            m_objects.insert(new Flames(IID_FLAME,a->getX()+i*SPRITE_WIDTH,a->getY()+j*SPRITE_HEIGHT,0,0,0,this));
        }
    m_objects.insert(new Pit(IID_PIT,a->getX(),a->getY(),0,0,0,this));
}
