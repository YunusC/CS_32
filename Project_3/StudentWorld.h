#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <sstream>
#include <iomanip>
#include <iterator>
#include <string>
#include <list>
#include <vector>
#include <set>

using namespace std;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp


class Object;
class Penelope;
class Exit;
class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void levelCompleted(){m_levelComplete = true;};
    void deadCitizen(){m_numOfCitizens--;};
    void failLevel(){m_levelFailed = true;};
    void destroy(Object* x);
    bool determineIntersecting(Object* x, double a, double b);
    int numOfCitizens(){return m_numOfCitizens;};
    bool overlap(double x, double y, Object* a, Object* b);
    bool isOverlapping(Object* a);
    void killOverlap(Object* a);
    void saveOverlap(Object* a);
    void infectOverlap(Object* a);
    void createFlames(Object* a, Direction dir);
    void activateLandmine(Object* a);
    Penelope* p(){return m_p;};
    
private:
    bool blockMovement(double x1, double y1, Object* x, Object* y);
    bool overlap(double x, double y);
    void infect(Object* a);
    void save(Object* a);
    Object* level(int x, int y);
    set<Object*>::iterator m_currObject;
    set<Object*> m_objects;
    Penelope* m_p;
    bool m_levelComplete;
    bool m_levelFailed;
    int m_numOfCitizens;
    char m_levelNum;
    int m_key;
    string m_gameStats;
    ostringstream m_gameStatStream;
};

#endif // STUDENTWORLD_H_
