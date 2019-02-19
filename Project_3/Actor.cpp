#include "Actor.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
void Object::destroy()
{
    m_exists = false;
}

void Exit::doSomething()
{
    if(studentWorld()->numOfCitizens() == 0)
    {
        if(studentWorld()->overlap(0,0,studentWorld()->p(),this))
        {
            studentWorld()->levelCompleted();
        }
    }
    
}

void Pit::doSomething()
{
    studentWorld()->killOverlap(this);
}

void Character::move(Direction dir)
{
    switch(dir)
    {
        case up:
            setDirection(up);
            if(!studentWorld()->determineIntersecting(this, getX(),getY()+m_moveSpeed))
               moveTo(getX(),getY()+m_moveSpeed);
            break;
        case down:
            setDirection(down);
            if(!studentWorld()->determineIntersecting(this, getX(),getY()-m_moveSpeed))
                moveTo(getX(),getY()-m_moveSpeed);
            break;
        case left:
            setDirection(left);
            if(!studentWorld()->determineIntersecting(this, getX()-m_moveSpeed,getY()))
                moveTo(getX()-m_moveSpeed,getY());
            break;
        case right:
            setDirection(right);
            if(!studentWorld()->determineIntersecting(this, getX()+m_moveSpeed,getY()))
                moveTo(getX()+m_moveSpeed,getY());
            break;
    }
}

void Penelope::doSomething(int key)
{
    increaseInfection();
    if(!isAlive())
    {
        studentWorld()->failLevel();
        studentWorld()->playSound(SOUND_PLAYER_DIE);
        return;
    }
    switch(key)
    {
        case KEY_PRESS_LEFT:
            move(left);
            break;
        case KEY_PRESS_RIGHT:
            move(right);
            break;
        case KEY_PRESS_UP:
            move(up);
            break;
        case KEY_PRESS_DOWN:
            move(down);
            break;
        case KEY_PRESS_SPACE:
            useFlames();
            break;
        case KEY_PRESS_TAB:
            useLandmines();
            break;
        case KEY_PRESS_ENTER:
            useVaccines();
        default:
            break;
    }
}

void Penelope::useVaccines()
{
    if(m_numOfVaccines <= 0)
        return;
    m_numOfVaccines--;
    disinfect();
}

void Penelope::useFlames()
{
    if(m_numOfFlames <= 0)
        return;
    studentWorld()->createFlames(this, this->getDirection());
    studentWorld()->playSound(SOUND_PLAYER_FIRE);
    m_numOfFlames--;
}

void Penelope::useLandmines()
{
    if(m_numOfLandmines <= 0)
        return;
    
}

void Citizens::save()
{
    studentWorld()->playSound(SOUND_CITIZEN_SAVED);
    studentWorld()->increaseScore(1000);
    destroy();
}
void dumbZombies::doSomething()
{
    move(randInt(0,3)*90);
}

void Flames::doSomething()
{
    if(tickCounter() == 0)
    {
        increaseTickCounter();
        return;
    }
    studentWorld()->killOverlap(this);
    destroy();
}

bool Items::pickedUp()
{
    if(studentWorld()->overlap(0,0,studentWorld()->p(),this))
    {
        studentWorld()->playSound(SOUND_GOT_GOODIE);
        studentWorld()->increaseScore(50);
        return true;
    }
    return false;
}

void Gas::doSomething()
{
    if(pickedUp())
    {
        studentWorld()->p()->pickUpFlames();
        destroy();
    }
}

void Vaccines::doSomething()
{
    if(pickedUp())
    {
        studentWorld()->p()->pickUpVaccines();
        destroy();
    }
}

void Landmines::doSomething()
{
    if(pickedUp())
    {
        studentWorld()->p()->pickUpLandmines();
        destroy();
    }
}

void armedLandmine::doSomething()
{
    if(tickCounter() < 30)
    {
        increaseTickCounter();
        return;
    }
    if(studentWorld()->isOverlapping(this))
    {
        studentWorld()->activateLandmine(this);
        destroy();
    }
}
