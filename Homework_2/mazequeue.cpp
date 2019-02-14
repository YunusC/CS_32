//
//  mazequeue.cpp
//  Homework_2
//
//  Created by Yunus Chang on 1/31/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <queue>

using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

void checkValidPath(queue<Coord> &coordStack, string maze[], int r, int c)
{
    if(maze[r][c] == '.')
    {
        Coord x(r, c);
        coordStack.push(x);
    }
}

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    queue<Coord> coordStack;
    coordStack.push(Coord(sr,sc));
    maze[sr][sc] = '#';
    while(!coordStack.empty())
    {
        Coord current(coordStack.front().r(),coordStack.front().c());
        coordStack.pop();
        maze[current.r()][current.c()] = '#';
        if(current.r() == er && current.c() == ec)
            return true;
        checkValidPath(coordStack, maze, current.r()+1, current.c());
        checkValidPath(coordStack, maze, current.r(), current.c()-1);
        checkValidPath(coordStack, maze, current.r()-1, current.c());
        checkValidPath(coordStack, maze, current.r(), current.c()+1);
    }
    return false;
}

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X....X...X",
        "X.XX.XX..X",
        "XXX....X.X",
        "X.XXX.XXXX",
        "X.X...X..X",
        "X...X.X..X",
        "XXXXX.X.XX",
        "X........X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 3,5 , 8,8))
    {
        for(int i = 0;i < 10; i++)
        {
            cout << maze[i] << endl;
        }
        cout << "Solvable!" << endl;
    }
    else
    {
        cout << "Out of luck!" << endl;
        for(int i = 0;i < 10; i++)
        {
            cout << maze[i] << endl;
        }
    }
}
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise




