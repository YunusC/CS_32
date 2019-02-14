//
//  testSet.cpp
//  Project_2
//
//  Created by Yunus Chang on 1/18/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//

#include "Set.h"
/*
int a()
{
    Set s;
    assert(s.empty());
    ItemType x = "arepa";
    assert( !s.get(42, x)  &&  x == "arepa"); // x unchanged by get failure
    s.insert("chapati");
    assert(s.size() == 1);
    assert(s.get(0, x)  &&  x == "chapati");
    
    Set ss;
    assert(ss.empty());
    ss.insert("lavash");
    ss.insert("roti");
    ss.insert("chapati");
    ss.insert("injera");
    ss.insert("roti");
    ss.insert("matzo");
    ss.insert("injera");
    assert(ss.size() == 5);  // duplicate "roti" and "injera" were not added
    string xy;
    ss.get(0, xy);
    assert(ss.contains("chapati"));
    assert(xy == "chapati");  // "chapati" is greater than exactly 0 items in ss
    ss.get(4, xy);
    assert(xy == "roti");  // "roti" is greater than exactly 4 items in ss
    ss.get(2, xy);
    assert(xy == "lavash");  // "lavash" is greater than exactly 2 items in ss
    
    swap(s,ss);
    assert(s.size() == 5);
    assert(ss.size() == 1);
    assert(!ss.erase("arepa"));
    assert(ss.erase("chapati"));
    assert(ss.empty());
    cout << "Passed all tests" << endl;
    return 0;
}
*/
#include "Set.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Set ss;
    assert(ss.insert("roti"));
    assert(ss.insert("pita"));
    assert(ss.size() == 2);
    assert(ss.contains("pita"));
    ItemType x = "laobing";
    assert(ss.get(0, x)  &&  x == "pita");
    assert(ss.get(1, x)  &&  x == "roti");
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
    }
