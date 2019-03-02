#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <iostream>
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;
class Object:public GraphObject
{
public:
    Object(int imageID, double startX, double startY, int depth, StudentWorld* sW):GraphObject(imageID,startX,startY,right,depth,1.0), m_studentWorld(sW), m_tickCounter(1), m_exists(true){};
    virtual void doSomething(){return;};
    StudentWorld* studentWorld(){return m_studentWorld;};
    void destroy();
    bool exists(){return m_exists;};
    virtual bool canMoveThrough(){return true;};
    virtual bool canDie(){return false;};
    virtual bool canOverlap(){return true;};
    virtual bool canFlameOverlap(){return true;};
    virtual bool canBeSaved(){return false;};
    virtual bool canBeInfected(){return false;};
    virtual void infect(){};
    virtual void save(){};
    virtual void flameDestroy(){};
    virtual void pitDestroy(){};
    virtual bool isZombie(){return false;};
    int tickCounter(){return m_tickCounter;};
    void increaseTickCounter(){m_tickCounter++;};
    void resetTickCounter(){m_tickCounter=1;};
private:
    StudentWorld* m_studentWorld;
    int m_tickCounter;
    bool m_exists;
};

class Wall:public Object
{
public:
    Wall(double startX, double startY, StudentWorld* sW):Object(IID_WALL, startX, startY, 0, sW){};
    virtual bool canMoveThrough(){return false;};
    virtual bool canOverlap(){return false;};
    virtual bool canFlameOverlap(){return false;};
private:
};

class Exit:public Object
{
public:
    Exit(double startX, double startY, StudentWorld* sW):Object(IID_EXIT, startX, startY, 1, sW){};
    virtual void doSomething();
    virtual bool canFlameOverlap(){return false;};
private:
};

class Pit:public Object
{
public:
    Pit(double startX, double startY, StudentWorld* sW):Object(IID_PIT, startX, startY, 0, sW){};
    virtual void doSomething();
private:
};

class Character:public Object
{
public:
    Character(int imageID, double startX, double startY, int depth, StudentWorld* sW):Object(imageID, startX, startY, depth, sW){};
    bool move(Direction dir);
    void setMoveSpeed(int moveSpeed){m_moveSpeed = moveSpeed;};
    int moveSpeed(){return m_moveSpeed;};
    virtual bool canMoveThrough(){return false;};
    virtual bool canDie(){return true;};
    virtual void flameDestroy(){destroy();};
    virtual void pitDestroy(){destroy();};
    int directToObject(int prevDir, Object* a);
private:
    bool canMove();
    double m_moveSpeed;
};

class nonInfected:public Character
{
public:
    nonInfected(int imageID, double startX, double startY, int depth, StudentWorld* sW):Character(imageID, startX, startY, depth, sW), m_infectionCount(0), m_infected(false), m_cInfected(false){};
    int infectionCount(){return m_infectionCount;};
    virtual bool canBeInfected(){return true;};
    virtual void infect(){m_infected = true;};
    void disinfect(){m_infected = false;m_infectionCount = 0;};
    bool isCompleteInfected(){return m_cInfected;};
    bool isInfected(){return m_infected;};
    void increaseInfection(){if(m_infected == true)m_infectionCount++;if(m_infectionCount >= 500)m_cInfected=true;};
private:
    void moveFast(Direction dir);
    int m_infectionCount;
    bool m_infected;
    bool m_cInfected;
};

class Penelope:public nonInfected
{
public:
    Penelope(double startX, double startY, StudentWorld* sW):nonInfected(IID_PLAYER, startX, startY, 0, sW)
    {m_numOfFlames = 0;m_numOfLandmines = 0;m_numOfVaccines = 0;setMoveSpeed(4);};
    virtual void doSomething();
    int numOfFlames(){return m_numOfFlames;};
    int numOfLandmines(){return m_numOfLandmines;};
    int numOfVaccines(){return m_numOfVaccines;};
    void pickUpFlames(){m_numOfFlames += 5;};
    void pickUpLandmines(){m_numOfLandmines++;};
    void pickUpVaccines(){m_numOfVaccines += 2;};
private:
    void useFlames();
    void useLandmines();
    void useVaccines();
    int m_numOfFlames;
    int m_numOfLandmines;
    int m_numOfVaccines;
};

class Citizens:public nonInfected
{
public:
    Citizens(double startX, double startY, StudentWorld* sW):nonInfected(IID_CITIZEN, startX, startY, 0, sW){setMoveSpeed(2);};
    ~Citizens();
    virtual void doSomething();
    virtual bool canBeSaved(){return true;};
    virtual void save();
    virtual void flameDestroy();
    virtual void pitDestroy();
    virtual void infect();
    bool becomeZombie();
    //void moveAwayFromZombies();
private:
};

class Zombies:public Character
{
public:
    Zombies(double startX, double startY, StudentWorld* sW):Character(IID_ZOMBIE, startX, startY, 0, sW), m_movePlan(0)
    {setMoveSpeed(1);};
    bool vomit();
    int movePlan(){return m_movePlan;};
    void setNewMovePlan(int movePlan){m_movePlan = movePlan;};
    virtual void determineNewPlan() = 0;
    virtual void doSomething();
    virtual bool isZombie(){return true;};
private:
    int m_movePlan;
};

class smartZombies:public Zombies
{
public:
    smartZombies(double startX, double startY, StudentWorld* sW):Zombies(startX, startY, sW){};
    virtual void flameDestroy();
    virtual void pitDestroy();
    virtual void determineNewPlan();
};

class dumbZombies:public Zombies
{
public:
    dumbZombies(double startX, double startY, StudentWorld* sW):Zombies(startX, startY, sW){};
    ~dumbZombies();
    virtual void flameDestroy();
    virtual void pitDestroy();
    virtual void determineNewPlan();
};

class Items:public Object
{
public:
    Items(int imageID, double startX, double startY, StudentWorld* sW):Object(imageID, startX, startY, 1, sW){};
    virtual void doSomething();
    virtual bool canDie(){return true;};
    virtual void flameDestroy(){destroy();};
    bool pickedUp();
private:
    virtual void whenPickedUp() = 0;
};

class Gas:public Items
{
public:
    Gas(double startX, double startY, StudentWorld* sW):Items(IID_GAS_CAN_GOODIE, startX, startY, sW){};
private:
     virtual void whenPickedUp();
};

class Vaccines:public Items
{
public:
    Vaccines(double startX, double startY, StudentWorld* sW):Items(IID_VACCINE_GOODIE, startX, startY, sW){};
private:
    virtual void whenPickedUp();
};

class Landmines:public Items
{
public:
    Landmines(double startX, double startY, StudentWorld* sW):Items(IID_LANDMINE_GOODIE, startX, startY, sW){};
private:
    virtual void whenPickedUp();
};

class armedLandmine:public Object
{
public:
    armedLandmine(double startX, double startY, StudentWorld* sW):Object(IID_LANDMINE, startX, startY, 0, sW){};
    virtual void doSomething();
private:
};

class Flames:public Object
{
public:
    Flames(double startX, double startY, Direction dir, StudentWorld* sW):Object(IID_FLAME, startX, startY, dir, sW){};
    virtual void doSomething();
private:
};

class Vomit:public Object
{
public:
    Vomit(double startX, double startY, StudentWorld* sW):Object(IID_VOMIT, startX, startY, 0, sW){};
    virtual void doSomething();
private:
};

bool overlap(Object& x, Object& y);
#endif // ACTOR_H_
