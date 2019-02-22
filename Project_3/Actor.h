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
   // Object(int imageID, double startX, double startY, StudentWorld* sW, Direction dir, int depth, double size);
    Object(int imageID, double startX, double startY, int depth, StudentWorld* sW):GraphObject(imageID,startX,startY,right,depth,1.0), m_studentWorld(sW), m_exists(true){};
    virtual void doSomething(){return;};
    StudentWorld* studentWorld(){return m_studentWorld;};
    void destroy();
    bool exists(){return m_exists;};
    virtual bool canMoveThrough(){return true;};
    virtual bool canDie(){return false;};
    virtual bool canOverlap(){return true;};
    virtual bool canBeSaved(){return false;};
    virtual bool canBeInfected(){return false;};
    virtual void infect(){};
    virtual void save(){};
    int tickCounter(){return m_tickCounter;};
    void increaseTickCounter(){m_tickCounter++;};
    void resetTickCounter(){m_tickCounter=0;};
private:
    StudentWorld* m_studentWorld;
    int m_tickCounter = 0;
    bool m_exists;
};

class Wall:public Object
{
public:
    Wall(double startX, double startY, StudentWorld* sW):Object(IID_WALL, startX, startY, 0, sW){};
    virtual bool canMoveThrough(){return false;};
    virtual bool canOverlap(){return false;};
private:
};

class Exit:public Object
{
public:
    Exit(double startX, double startY, StudentWorld* sW):Object(IID_EXIT, startX, startY, 1, sW){};
    virtual void doSomething();
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
    void move(Direction dir);
    void setMoveSpeed(int moveSpeed){m_moveSpeed = moveSpeed;};
    virtual bool canMoveThrough(){return false;};
    virtual bool canDie(){return true;};
    void moveToPenelope(){};
    void randomMovement(){};
private:
    bool canMove();
    double m_moveSpeed;
};

class nonInfected:public Character
{
public:
    nonInfected(int imageID, double startX, double startY, int depth, StudentWorld* sW):Character(imageID, startX, startY, depth, sW), m_infectionCount(0), m_infected(false)
    {
    };
    int infectionCount(){return m_infectionCount;};
    virtual bool canBeInfected(){return true;};
    virtual void infect(){m_infected = true;};
    void disinfect(){m_infected = false;m_infectionCount = 0;};
    bool isAlive(){if(m_alive == false)return true; return false;};
    void increaseInfection(){if(m_infected == true)m_infectionCount++;if(m_infectionCount >= 500)m_alive=false;};
private:
    void moveFast(Direction dir);
    bool m_alive;
    bool m_infected;
    int m_infectionCount;
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
    virtual bool canBeSaved(){return true;};
    virtual void save();
    void moveAwayFromZombies();
private:
};

class Zombies:public Character
{
public:
    Zombies(double startX, double startY, StudentWorld* sW):Character(IID_ZOMBIE, startX, startY, 0, sW)
    {setMoveSpeed(1);};
    void vomit();
private:
};

class smartZombies:public Zombies
{
public:
    smartZombies(double startX, double startY, StudentWorld* sW):Zombies(startX, startY, sW){};
};

class dumbZombies:public Zombies
{
public:
    dumbZombies(double startX, double startY, StudentWorld* sW):Zombies(startX, startY, sW){};
    virtual void doSomething();
};

class Items:public Object
{
public:
    Items(int imageID, double startX, double startY, StudentWorld* sW):Object(imageID, startX, startY, 0, sW){};
    virtual void doSomething();
    bool pickedUp();
private:
    virtual void whenPickedUp()=0;
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
    Flames(double startX, double startY, StudentWorld* sW):Object(IID_FLAME, startX, startY, 0, sW){};
    virtual void doSomething();
private:
};

bool overlap(Object& x, Object& y);
#endif // ACTOR_H_
