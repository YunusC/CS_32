//
//  maze.cpp
//  Homework_3
//
//  Created by Yunus Chang on 2/7/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if(sr == er && sc == ec)
    {
        maze[sr][sc] = '@';
        return true;
    }
    maze[sr][sc] = '#';
    if(maze[sr+1][sc] == '.' && pathExists(maze,nRows,nCols,sr+1,sc,er,ec))
        return true;
    if(maze[sr][sc-1] == '.' && pathExists(maze,nRows,nCols,sr,sc-1,er,ec))
        return true;
    if(maze[sr-1][sc] == '.' && pathExists(maze,nRows,nCols,sr-1,sc,er,ec))
        return true;
    if(maze[sr][sc+1] == '.' && pathExists(maze,nRows,nCols,sr,sc+1,er,ec))
        return true;
    return false;
}


