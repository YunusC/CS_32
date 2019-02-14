//
//  History.cpp
//  Project_1
//
//  Created by Yunus Chang on 1/10/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//

#include "History.h"
using namespace std;
#include <iostream>

History::History(int nRows, int nCols)
:m_record{0}
{
    m_rows = nRows;
    m_cols = nCols;
}

bool History::record(int r, int c)
{
    if(r < 1 || r > MAXROWS || c < 1 || c > MAXCOLS)
        return false;
    m_record[r][c]++;
    return true;
}

void History::display() const
{
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 1; r <= m_rows; r++)
    {
        for (c = 1; c <= m_cols; c++)
        {
            if(m_record[r][c] == 0)
            {
            grid[r-1][c-1] = '.';
            }
            if(m_record[r][c] > 0)
            {
                grid[r-1][c-1] = 64 + m_record[r][c];
            }
            if(m_record[r][c] >= 26)
            {
                grid[r-1][c-1] = 'Z';
            }
        }
    }
    clearScreen();
    for (r = 0; r < m_rows; r++)
    {
        for (c = 0; c < m_cols; c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
}
