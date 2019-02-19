#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
#include <iostream>
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;
class Object:public GraphObject
{
public:
   // Object(int imageID, double startX, double startY, StudentWorld* sW, Direction dir, int depth, double size);
    Object(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* sW):GraphObject(imageID,startX,startY,dir,depth,size), m_studentWorld(sW), m_exists(true){};
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
    int tickCounter(){return m_tickCounter;} const;
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
    Wall(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* sW):Object(imageID, startX, startY, right, 0, size, sW){};
    virtual bool canMoveThrough(){return false;};
    virtual bool canOverlap(){return false;};
private:
};

class Exit:public Object
{
public:
    Exit(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* sW):Object(imageID, startX, startY, right, 1, size, sW){};
    virtual void doSomething();
private:
};

class Pit:public Object
{
public:
    Pit(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* sW):Object(imageID, startX, startY, right, 0, size, sW){};
    virtual void doSomething();
private:
};

class Character:public Object
{
public:
    Character(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* sW):Object(imageID, startX, startY, dir, depth, size, sW){};
    void move(Direction dir);
    void setMoveSpeed(int moveSpeed){m_moveSpeed = moveSpeed;};
    virtual bool canMoveThrough(){return false;};
    virtual bool canDie(){return true;};
private:
    bool canMove();
    double m_moveSpeed;
};

class nonInfected:public Character
{
public:
    nonInfected(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* sW):Character(imageID, startX, startY, dir, depth, size, sW)
    {
        setMoveSpeed(4);
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
    Penelope(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* sW):nonInfected(imageID, startX, startY, dir, depth, size, sW)
    {
        m_numOfFlames = 0;m_numOfLandmines = 0;m_numOfVaccines = 0;
    };
    void doSomething(int key);
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
    Citizens(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* sW):nonInfected(imageID, startX, startY, dir, depth, size, sW){};
    virtual bool canBeSaved(){return true;};
    virtual void save();
private:
    
};

class Zombies:public Character
{
public:
    Zombies(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* sW):Character(imageID, startX, startY, dir, depth, size, sW)
    {
        setMoveSpeed(1);
    };
private:
};

class smartZombies:public Zombies
{
public:
    smartZombies(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* sW):Zombies(imageID, startX, startY, dir, depth, size, sW){};
};

class dumbZombies:public Zombies
{
public:
    dumbZombies(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* sW):Zombies(imageID, startX, startY, dir, depth, size, sW){};
    virtual void doSomething();
};

class Items:public Object
{
public:
    Items(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* sW):Object(imageID, startX, startY, dir, 1, size, sW){};
    bool pickedUp();
};

class Gas:public Items
{
public:
    Gas(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* sW):Items(imageID, startX, startY, dir, depth, size, sW){};
    virtual void doSomething();
};

class Vaccines:public Items
{
public:
    Vaccines(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* sW):Items(imageID, startX, startY, dir, depth, size, sW){};
    virtual void doSomething();
};

class Landmines:public Items
{
public:
    Landmines(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* sW):Items(imageID, startX, startY, right, 1, size, sW){};
    virtual void doSomething();
};

class armedLandmine:public Object
{
public:
    armedLandmine(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* sW):Object(imageID, startX, startY, dir, depth, size, sW){};
    virtual void doSomething();
private:
};

class Flames:public Object
{
public:
    Flames(int imageID, double startX, double startY, Direction dir, int depth, double size, StudentWorld* sW):Object(imageID, startX, startY, dir, depth, size, sW){};
    virtual void doSomething();
private:
};

bool overlap(Object& x, Object& y);
#endif // ACTOR_H_
