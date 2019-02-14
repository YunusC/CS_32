//
//  main.cpp
//  Project_3_Warmup
//
//  Created by Yunus Chang on 2/14/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//

#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

// Remove the odd integers from li.
// It is acceptable if the order of the remaining even integers is not
// the same as in the original list.
void removeOdds(list<int>& li)
{
    list<int>::iterator i;
    if(li.empty())
        return;
    i = li.begin();
    while(i != li.end())
    {
        if(*i %2 == 1)
        {
            li.erase(i);
        }
        i++;
    }
}

void removeOdds(vector<int>& v)
{
    if(v.empty())
        return;
    vector<int>::iterator i;
    for(int i = 0;i < v.size();i++)
    {
        if(v[i] %2 == 1)
            v.erase(v.begin() + i);
    }
}

void test2()
{
    int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
    vector<int> x(a, a+8);  // construct x from the array
    assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
    removeOdds(x);
    cerr << x.size() << endl;
    assert(x.size() == 4);
    sort(x.begin(), x.end());
    int expect[4] = { 2, 4, 6, 8 };
    for (int k = 0; k < 4; k++)
        assert(x[k] == expect[k]);
}

void test()
{
    int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
    list<int> x(a, a+8);  // construct x from the array
    assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
    removeOdds(x);
    assert(x.size() == 4);
    vector<int> v(x.begin(), x.end());  // construct v from x
    sort(v.begin(), v.end());
    int expect[4] = { 2, 4, 6, 8 };
    for (int k = 0; k < 4; k++)
        assert(v[k] == expect[k]);
}

int main()
{
    cout << 'b' << endl;
    test();
    test2();
    cout << "Passed" << endl;
}
