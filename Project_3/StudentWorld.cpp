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
: GameWorld(assetPath), m_levelComplete(false), m_levelFailed(false), m_numOfCitizens(0), m_levelNum(1)
{
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    Level lev(assetPath());
    stringstream levelNum;
    levelNum.fill('0');
    levelNum << setw(2) << m_levelNum;
    string levelText = levelNum.str();
    string levelFile = "level"+levelText+".txt";
    Level::LoadResult result = lev.loadLevel(levelFile);
    if (result == Level::load_fail_file_not_found && m_levelNum != 1)
    {
        return GWSTATUS_PLAYER_WON;
        
    }
    else if (result == Level::load_fail_bad_format)
    {
        return GWSTATUS_LEVEL_ERROR;
    }
    else if (result == Level::load_success)
    {
        Object* newObject;
        for(int x = 0;x < LEVEL_WIDTH;x++)
        {
            for(int y = 0;y < LEVEL_HEIGHT;y++)
            {
                newObject = level(x, y, levelFile);
                if(newObject != nullptr)
                {
                    m_objects.insert(newObject);
                }
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    if(!m_p->exists())
    {
        playSound(SOUND_PLAYER_DIE);
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    if(m_levelComplete == true)
    {
        m_levelNum++;
        m_levelComplete = false;
        playSound(SOUND_LEVEL_FINISHED);
        return GWSTATUS_FINISHED_LEVEL;
    }
    m_p->doSomething();
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
    if(getScore() < 0)
    {
        m_gameStatStream << '-' << setw(5) << -getScore();
    }
    else
    {
        m_gameStatStream << setw(6) << getScore();
    }
    m_gameStatStream.fill(' ');
    m_gameStatStream << "  Level: " << setw(2) << m_levelNum << "  Lives: " << setw(2) << getLives();
    m_gameStatStream << "  Vacc: " << setw(2) << m_p->numOfVaccines();
    m_gameStatStream << "  Flames: " << setw(2) << m_p->numOfFlames();
    m_gameStatStream << "  Mines: " << setw(2) << m_p->numOfLandmines();
    m_gameStatStream << "  Infected: " << setw(3) << m_p->infectionCount();
    m_gameStats = "";
    setGameStatText("");
    m_gameStats = m_gameStatStream.str();
    setGameStatText(m_gameStats);
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    m_currObject = m_objects.begin();
    if(m_p == nullptr && m_currObject == m_objects.end())
        return;
    delete m_p;
    m_p = nullptr;
    while(!m_objects.empty() && m_currObject != m_objects.end())
    {
        delete (*m_currObject);
        m_objects.erase(m_currObject);
        m_currObject = m_objects.begin();
    }
}

Object* StudentWorld::level(int x, int y, string levelFile)
{
    Level lev(assetPath());
    lev.loadLevel(levelFile);
    Level::MazeEntry ge = lev.getContentsOf(x,y); // level_x=5, level_y=10
        switch (ge) // so x=80 and y=160
        {
            case Level::empty:
                break;
            case Level::smart_zombie:
                return new smartZombies(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this);
                break;
            case Level::dumb_zombie:
                return new dumbZombies(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this);
                break;
            case Level::player:
                m_p = new Penelope(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this);
                break;
            case Level::exit:
                return new Exit(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this);
                break;
            case Level::wall:
                return new Wall(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this);
                break;
            case Level::pit:
                return new Pit(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this);
                break;
            case Level::citizen:
                m_numOfCitizens++;
                return new Citizens(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this);
                break;
            case Level::landmine_goodie:
                return new Landmines(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this);
                break;
            case Level::vaccine_goodie:
                return new Vaccines(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this);
                break;
            case Level::gas_can_goodie:
                return new Gas(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,this);
                break;
        }
    return nullptr;
}

//excellent way to destroy objects

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
    if(blockMovement(a,b,x,m_p))
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

void StudentWorld::pitOverlap(Object* a)
{
    set<Object*>::iterator i;
    i = m_objects.begin();
    if(overlap(0,0,a,m_p))
        m_p->pitDestroy();
    while(i != m_objects.end())
    {
        if(overlap(0,0,a,*i) && (*i)->canDie())
            (*i)->pitDestroy();
        i++;
    }
}

void StudentWorld::flameOverlap(Object* a)
{
    set<Object*>::iterator i;
    i = m_objects.begin();
    if(overlap(0,0,a,m_p))
        m_p->flameDestroy();
    while(i != m_objects.end())
    {
        if(overlap(0,0,a,*i) && (*i)->canDie())
            (*i)->flameDestroy();
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
    if(overlap(0,0,a,m_p))
        m_p->infect();
    while(i != m_objects.end())
    {
        if(overlap(0,0,a,*i) && (*i)->canBeInfected())
            (*i)->infect();
        i++;
    }
}

bool StudentWorld::canVomit(double x, double y, Object* a)
{
    set<Object*>::iterator i;
    i = m_objects.begin();
    bool canVomit = false;
    if(overlap(x,y,a,m_p))
    {
        canVomit = true;
    }
    while(i != m_objects.end())
    {
        if(overlap(x,y,a,*i) && (*i)->canBeInfected())
            canVomit = true;
        i++;
    }
    if(canVomit && (1 == randInt(1,3)))
    {
        m_objects.insert(new Vomit(a->getX()+x,a->getY()+y,this));
        return true;
    }
    return false;
}

void StudentWorld::createZombie(int zType, Object* a)
{
    if(1 <= zType && zType <= 3)
        m_objects.insert(new smartZombies(a->getX(), a->getY(), this));
    if(4 <= zType && zType <= 10)
        m_objects.insert(new dumbZombies(a->getX(), a->getY(), this));
}

bool StudentWorld::isOverlapping(Object* a)
{
    set<Object*>::iterator x;
    x = m_objects.begin();
    if(overlap(0,0,a,m_p))
        return true;
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
                if(overlap(0,i*SPRITE_HEIGHT,a,*x) && !(*x)->canFlameOverlap())
                    return;
                break;
            case Character::down:
                if(overlap(0,-(i*SPRITE_HEIGHT),a,*x) && !(*x)->canFlameOverlap())
                    return;
                break;
            case Character::left:
                if(overlap(-(i*SPRITE_WIDTH),0,a,*x) && !(*x)->canFlameOverlap())
                    return;
                break;
            case Character::right:
                if(overlap(i*SPRITE_WIDTH,0,a,*x) && !(*x)->canFlameOverlap())
                    return;
                break;
        }
            x++;
        }
        switch(dir)
        {
            case Character::up:
                m_objects.insert(new Flames(a->getX(),a->getY()+i*SPRITE_HEIGHT, 0, this));
                break;
            case Character::down:
                m_objects.insert(new Flames(a->getX(),a->getY()-i*SPRITE_HEIGHT, 0, this));
                break;
            case Character::left:
                m_objects.insert(new Flames(a->getX()-i*SPRITE_WIDTH,a->getY(), 0, this));
                break;
            case Character::right:
                m_objects.insert(new Flames(a->getX()+i*SPRITE_WIDTH,a->getY(), 0, this));
                break;
        }
        i++;
    }
}

void StudentWorld::createLandmine(){m_objects.insert(new armedLandmine(m_p->getX(), m_p->getY(),this));}

void StudentWorld::createRandItem(Object* a)
{
    int x = 0;
    int y = 0;
    switch(randInt(0,3))
    {
        case 0:
            x = 1;
            break;
        case 1:
            y = 1;
            break;
        case 2:
            x = -1;
            break;
        case 3:
            y = -1;
            break;
    }
    bool doesOverlap = false;
    set<Object*>::iterator i;
    i = m_objects.begin();
    while(i != m_objects.end())
    {
        if(overlap(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,a,*i))
            doesOverlap = true;
        i++;
    }
    if(!doesOverlap)
    {
        switch(randInt(0,2))
        {
            case 0:
                m_objects.insert(new Gas(a->getX()+SPRITE_WIDTH*x,a->getY()+SPRITE_HEIGHT*y,this));
                break;
            case 1:
                m_objects.insert(new Vaccines(a->getX()+SPRITE_WIDTH*x,a->getY()+SPRITE_HEIGHT*y,this));
                break;
            case 2:
                m_objects.insert(new Landmines(a->getX()+SPRITE_WIDTH*x,a->getY()+SPRITE_HEIGHT*y,this));
                break;
        }
    }
}

void StudentWorld::activateLandmine(Object* a)
{
    set<Object*>::iterator x;
    x = m_objects.begin();
    bool canFlame = true;
    for(int i = -1;i < 2;i++)
        for(int j= -1;j < 2;j++)
        {
            while(x != m_objects.end())
            {
                if(overlap(i*SPRITE_WIDTH,j*SPRITE_HEIGHT,a,*x) && !(*x)->canOverlap())
                    {
                        canFlame = false;
                        break;
                    }
                else
                    x++;
            }
            if(canFlame)
                m_objects.insert(new Flames(a->getX()+i*SPRITE_WIDTH,a->getY()+j*SPRITE_HEIGHT, 90, this));
            else
                canFlame = true;
            x = m_objects.begin();
        }
    m_objects.insert(new Pit(a->getX(),a->getY(),this));
}

double StudentWorld::determineDistance(double x, double y, Object* a, Object* b)
{
    if(b == nullptr)
        return 6401;
    double deltaX = (a->getX()+x) - b->getX();
    double deltaY = (a->getY()+y) - b->getY();
    return (deltaX*deltaX + deltaY*deltaY);
}

Object* StudentWorld::closestZombie(double x, double y, Object* a)
{
    Object* closestObject = nullptr;
    set<Object*>::iterator i;
    i = m_objects.begin();
    double minDistance = 6400;
    double thisDistance = 0;
    while(i != m_objects.end())
    {
        thisDistance = determineDistance(x, y, a, *i);
        if((thisDistance <= minDistance) && ((*i)->isZombie()))
        {
            minDistance = thisDistance;
            closestObject = (*i);
        }
        i++;
    }
    return closestObject;
}

Object* StudentWorld::closestNonInfected(Object* a)
{
    Object* closestObject = nullptr;
    set<Object*>::iterator i;
    i = m_objects.begin();
    double minDistance = 6400;
    double thisDistance = determineDistance(0, 0, a, m_p);
    if(thisDistance <= 6400)
    {
        minDistance = thisDistance;
        closestObject = m_p;
    }
    while(i != m_objects.end())
    {
        thisDistance = determineDistance(0, 0, a, *i);
        if((thisDistance <= minDistance) && ((*i)->canBeInfected()))
        {
            minDistance = thisDistance;
            closestObject = (*i);
        }
        i++;
    }
    return closestObject;
}
