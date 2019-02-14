//
//  main.cpp
//  Project_2
//
//  Created by Yunus Chang on 1/16/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//

/*
#include <iostream>
#include <string>
#include <cassert>
#include "Set.h"
#include "newSet.h"
#include "SSNSet.h"
using namespace std;

int main()
{
    b();
    c();
    return 0;
}
*/
#include "newSet.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Set uls;
    assert(uls.insert(20));
    assert(uls.insert(10));
    assert(uls.size() == 2);
    assert(uls.contains(10));
    ItemType x = 30;
    assert(uls.get(0, x)  &&  x == 10);
    assert(uls.get(1, x)  &&  x == 20);
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}
