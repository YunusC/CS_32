//
//  testSSNSet.cpp
//  Homework_1
//
//  Created by Yunus Chang on 1/22/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//

#include "SSNSet.h"
#include <iostream>
#include <cassert>

using namespace std;
int main()
{
    SSNSet s;

    s.add(611234536);
    s.add(234523562);
    s.add(325363452);
    s.add(611236833);
    s.add(234524562);
    assert(s.size() == 5);
    s.print();
    cout << "Passed all tests" << endl;
    return 0;
}

