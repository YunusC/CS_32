//
//  History.hpp
//  Project_1
//
//  Created by Yunus Chang on 1/10/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//

#ifndef History_hpp
#define History_hpp

#include <stdio.h>
#include "globals.h"
class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_rows;
    int m_cols;
    int m_record[MAXROWS+1][MAXCOLS+1];
};
#endif /* History_hpp */
