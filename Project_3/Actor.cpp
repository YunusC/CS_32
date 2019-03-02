#include "Actor.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
void Object::destroy(){m_exists = false;}

void Exit::doSomething()
{
    if(studentWorld()->numOfCitizens() == 0)
    {
        if(studentWorld()->overlap(0,0,studentWorld()->p(),this))
        {
            studentWorld()->levelCompleted();
        }
    }
    studentWorld()->saveOverlap(this);
}

void Pit::doSomething(){studentWorld()->pitOverlap(this);}

bool Character::move(Direction dir)
{
    switch(dir)
    {
        case up:
            setDirection(up);
            if(!studentWorld()->determineIntersecting(this, getX(),getY()+m_moveSpeed))
            {
                moveTo(getX(),getY()+m_moveSpeed);return true;
            }
            break;
        case down:
            setDirection(down);
            if(!studentWorld()->determineIntersecting(this, getX(),getY()-m_moveSpeed))
            {
                moveTo(getX(),getY()-m_moveSpeed);return true;
            }
            break;
        case left:
            setDirection(left);
            if(!studentWorld()->determineIntersecting(this, getX()-m_moveSpeed,getY()))
            {
                moveTo(getX()-m_moveSpeed,getY());return true;
            }
            break;
        case right:
            setDirection(right);
            if(!studentWorld()->determineIntersecting(this, getX()+m_moveSpeed,getY()))
            {
                moveTo(getX()+m_moveSpeed,getY());return true;
            }
            break;
    }
    return false;
}

int Character::directToObject(int prevDir, Object* a)
{
    if(getX() == a->getX())
    {
        if(getY() < a->getY())
            return up;
        else
            return down;
    }
    if(getY() == a->getY())
    {
        if(getX() < a->getX())
            return right;
        else
            return left;
    }
    int direction;
    if(getX() < a->getX())//1 is right; 2 is left
        direction = 1;
    else
        direction = 2;
    if(getY() < a->getY())//positive is up; negative is down
        direction = direction;
    else
        direction = -direction;
    int newDir;
    switch(direction)
    {
        case -2:
            newDir = randInt(2,3)*90;
            if(newDir == prevDir)
            {
                if(prevDir == left)
                    return down;
                if(prevDir == down)
                    return left;
            }
            return newDir;
            break;
        case -1:
            newDir = randInt(0,1)*270;
            if(newDir == prevDir)
            {
                if(prevDir == right)
                    return down;
                if(prevDir == down)
                    return right;
            }
            return newDir;
            break;
        case 1:
            newDir = randInt(0,1)*90;
            if(newDir == prevDir)
            {
                if(prevDir == right)
                    return up;
                if(prevDir == up)
                    return right;
            }
            return newDir;
            break;
        case 2:
            newDir = randInt(1,2)*90;
            if(newDir == prevDir)
            {
                if(prevDir == up)
                    return left;
                if(prevDir == left)
                    return up;
            }
            return newDir;
            break;
    }
    return -1;
}

void Penelope::doSomething()
{
    increaseInfection();
    if(!exists())
        return;
    if(isCompleteInfected())
    {
        destroy();
        return;
    }
    int key;
    studentWorld()->getKey(key);
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
    m_numOfFlames--;
    studentWorld()->createFlames(this, this->getDirection());
    studentWorld()->playSound(SOUND_PLAYER_FIRE);
}

void Penelope::useLandmines()
{
    if(m_numOfLandmines <= 0)
        return;
    studentWorld()->createLandmine();
}

void Citizens::doSomething()
{
    if(!exists())
        return;
    increaseInfection();
    if(becomeZombie())
        return;
    if(tickCounter() == 1)
    {
        increaseTickCounter();
        return;
    }
    double distToP = studentWorld()->determineDistance(0, 0, this, studentWorld()->p());
    double distToZ = distToP + 1;
    Object* closestZombie = studentWorld()->closestZombie(0, 0, this);
    if(closestZombie != nullptr)
        distToZ = studentWorld()->determineDistance(0,0, this, closestZombie);
    if(distToP < distToZ && distToP <= 6400)
    {
        setDirection(directToObject(-1, studentWorld()->p()));
        if(!move(getDirection()))
           {
               setDirection(directToObject(getDirection(), studentWorld()->p()));
               if(move(getDirection()))
               {
                   resetTickCounter();
                   return;
               }
           }
        else
        {
            resetTickCounter();
            return;
        }
    }
    if(distToZ <= 6400 && closestZombie != nullptr)
    {
        double x = getX() - closestZombie->getX();
        if(x < 0) x = -x;
        double y = getY() - closestZombie->getY();
        if(y < 0) y = -y;
        int prevDir;
        if(y == 0)
        {
            setDirection(prevDir = randInt(0,1)*180 + 90);
            if(!move(getDirection()))
            {
                if(prevDir == up)
                setDirection(down);
                if(prevDir == down)
                    setDirection(up);
                move(getDirection());
                resetTickCounter();
                return;
            }
            else
            {
                resetTickCounter();
                return;
            }
        }
        if(x == 0)
        {
            setDirection(prevDir = randInt(0,1)*180);
            if(!move(getDirection()))
            {
                if(prevDir == right)
                    setDirection(left);
                if(prevDir == left)
                    setDirection(right);
                move(getDirection());
                resetTickCounter();
                return;
            }
            else
            {
                resetTickCounter();
                return;
            }
        }
        int direction;
        if(getX() < closestZombie->getX())//1 is right; 2 is left
            direction = 2;
        else
            direction = 1;
        if(getY() < closestZombie->getY())//positive is up; negative is down
            direction = -direction;
        else
            direction = direction;
        switch(direction)
        {
            case -2:
                if(y < x)
                    if(!studentWorld()->determineIntersecting(this, getX(), getY()-moveSpeed()) && (distToZ < studentWorld()->determineDistance(0, -2, this, studentWorld()->closestZombie(0, -2, this))))
                    {
                        move(down);
                        break;
                    }
                if(!studentWorld()->determineIntersecting(this, getX()-moveSpeed(), getY()) && (distToZ < studentWorld()->determineDistance(-2, 0, this, studentWorld()->closestZombie(-2, 0, this))))
                    {
                        move(left);
                        break;
                    }
                break;
            case -1:
                if(x < y)
                    if(!studentWorld()->determineIntersecting(this, getX(), getY()-moveSpeed()) && (distToZ < studentWorld()->determineDistance(0, -2, this, studentWorld()->closestZombie(0, -2, this))))
                    {
                        move(down);
                        break;
                    }
                if(!studentWorld()->determineIntersecting(this, getX()+moveSpeed(), getY()) && (distToZ < studentWorld()->determineDistance(2, 0, this, studentWorld()->closestZombie(2, 0, this))))
                {
                    move(right);
                    break;
                }
                break;
            case 1:
                if(x < y)
                    if(!studentWorld()->determineIntersecting(this, getX(), getY()+moveSpeed()) && (distToZ < studentWorld()->determineDistance(0, 2, this, studentWorld()->closestZombie(0, 2, this))))
                    {
                        move(up);
                        break;
                    }
                if(!studentWorld()->determineIntersecting(this, getX()+moveSpeed(), getY()) && (distToZ < studentWorld()->determineDistance(2, 0, this, studentWorld()->closestZombie(2, 0, this))))
                {
                    move(right);
                    break;
                }
                break;
            case 2:
                if(y < x)
                    if(!studentWorld()->determineIntersecting(this, getX(), getY()+moveSpeed()) && (distToZ < studentWorld()->determineDistance(0, 2, this, studentWorld()->closestZombie(0, 2, this))))
                    {
                        move(up);
                        break;
                    }
                if(!studentWorld()->determineIntersecting(this, getX()-moveSpeed(), getY()) && (distToZ < studentWorld()->determineDistance(-2, 0, this, studentWorld()->closestZombie(-2, 0, this))))
                {
                    move(left);
                    break;
                }
                break;
        }
    }
    resetTickCounter();
}

void Citizens::infect()
{
    if(!isInfected())
    {
        studentWorld()->playSound(SOUND_CITIZEN_INFECTED);
        nonInfected::infect();
    }
}

void Citizens::save()
{
    studentWorld()->playSound(SOUND_CITIZEN_SAVED);
    studentWorld()->increaseScore(500);
    destroy();
}

bool Citizens::becomeZombie()
{
    if(isCompleteInfected())
    {
        studentWorld()->createZombie(randInt(1,10),this);
        studentWorld()->playSound(SOUND_ZOMBIE_BORN);
        studentWorld()->increaseScore(-1000);
        destroy();
        return true;
    }
    return false;
}

Citizens::~Citizens(){studentWorld()->decreaseCitizens();}

void Zombies::doSomething()
{
    if(!exists())
        return;
    if(tickCounter() == 1)
    {
        increaseTickCounter();
        return;
    }
    if(vomit())
    {
        studentWorld()->playSound(SOUND_ZOMBIE_VOMIT);
        return;
    }
    if(m_movePlan == 0)
        determineNewPlan();
    if(!move(getDirection()))
    {
        m_movePlan = 0;
        return;
    }
    m_movePlan--;
    resetTickCounter();
}

bool Zombies::vomit()
{
    double x = 0;
    double y = 0;
    switch(getDirection())
    {
        case up:
            y = SPRITE_HEIGHT;
            break;
        case down:
            y = -SPRITE_HEIGHT;
            break;
        case right:
            x = SPRITE_WIDTH;
            break;
        case left:
            x = -SPRITE_WIDTH;
            break;
    }
    if(studentWorld()->canVomit(x, y, this))
    {
        return true;
    }
    return false;
}

void dumbZombies::determineNewPlan()
{
    setDirection(randInt(0,3)*90);
    setNewMovePlan(randInt(3, 10));
}

dumbZombies::~dumbZombies()
{
    if(randInt(1, 10) == 1)
        studentWorld()->createRandItem(this);
}

void smartZombies::determineNewPlan()
{
    Object* closestNonInfected = studentWorld()->closestNonInfected(this);
    setNewMovePlan(randInt(3, 10));
    if(closestNonInfected == nullptr)
    {
        setDirection(randInt(0,3)*90);
        return;
    }
    setDirection(directToObject(-1, closestNonInfected));
}

void Flames::doSomething()
{
    studentWorld()->flameOverlap(this);
    if(tickCounter() == 1)
    {
        increaseTickCounter();
        return;
    }
    destroy();
}

void Citizens::flameDestroy(){studentWorld()->increaseScore(-1000);                                studentWorld()->playSound(SOUND_CITIZEN_DIE);destroy();}
void smartZombies::flameDestroy(){studentWorld()->increaseScore(2000);studentWorld()->playSound(SOUND_ZOMBIE_DIE); destroy();}
void dumbZombies::flameDestroy(){studentWorld()->increaseScore(1000);studentWorld()->playSound(SOUND_ZOMBIE_DIE); destroy();}

void Citizens::pitDestroy(){studentWorld()->increaseScore(-1000);studentWorld()->playSound(SOUND_CITIZEN_DIE);destroy();}
void smartZombies::pitDestroy(){studentWorld()->increaseScore(2000);studentWorld()->playSound(SOUND_ZOMBIE_DIE); destroy();}
void dumbZombies::pitDestroy(){studentWorld()->increaseScore(1000);studentWorld()->playSound(SOUND_ZOMBIE_DIE); destroy();}

void Vomit::doSomething()
{
    studentWorld()->infectOverlap(this);
    if(tickCounter() <= 3)
        destroy();
    increaseTickCounter();
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

void Items::doSomething(){if(pickedUp()){whenPickedUp();destroy();}}
void Gas::whenPickedUp(){studentWorld()->p()->pickUpFlames();}
void Landmines::whenPickedUp(){studentWorld()->p()->pickUpLandmines();}
void Vaccines::whenPickedUp(){studentWorld()->p()->pickUpVaccines();}

void armedLandmine::doSomething()
{
    if(tickCounter() <= 30)
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
