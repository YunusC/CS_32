//
//  testnewSet.cpp
//  Project_2
//
//  Created by Yunus Chang on 1/18/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//

#include "newSet.h"
/*
int b()
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
    
    Set sss = s;
    ss = s;
    ss.get(0, xy);
    assert(ss.contains("chapati"));
    assert(xy == "chapati");  // "chapati" is greater than exactly 0 items in ss
    ss.get(4, xy);
    assert(xy == "roti");  // "roti" is greater than exactly 4 items in ss
    ss.get(2, xy);
    assert(xy == "lavash");  // "lavash" is greater than exactly 2 items in ss
    
    sss.get(0, xy);
    assert(sss.contains("chapati"));
    assert(xy == "chapati");  // "chapati" is greater than exactly 0 items in ss
    sss.get(4, xy);
    assert(xy == "roti");  // "roti" is greater than exactly 4 items in ss
    sss.get(2, xy);
    assert(xy == "lavash");  // "lavash" is greater than exactly 2 items in ss
    cout << "Passed all tests" << endl;
    
    
    
    //split here
    
    Set s1;
    assert(s1.empty());
    ItemType x = 9876543;
    assert( !s1.get(42, x)  &&  x == 9876543); // x unchanged by get failure
    s1.insert(123456789);
    assert(s1.size() == 1);
    assert(s1.get(0, x)  &&  x == 123456789);
    
    
    Set a1(1000);   // a can hold at most 1000 distinct items
    Set b(5);      // b can hold at most 5 distinct items
    Set c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
    ItemType v[6] = {1,2,3,4,5,6};
    
    // No failures inserting 5 distinct items into b
    for (int k = 0; k < 5; k++)
        assert(b.insert(v[k]));
    
    // Failure if we try to insert a sixth distinct item into b
    assert(!b.insert(v[5]));
    
    // When two Sets' contents are swapped, their capacities are swapped
    // as well:
    a1.swap(b);
    assert(!a1.insert(v[5])  &&  b.insert(v[5]));
    
    Set s, a;
    assert(s.empty() && a.empty());
    ItemType xx = 12;
    assert( !s.get(42, xx)  &&  xx == 12); // x unchanged by get failure
    s.insert(45);
    s.insert(64);
    s.insert(3);
    s.insert(3);
    s.insert(6);
    s.insert(1532);
    assert(!s.erase(67));
    
    a.insert(634);
    a.insert(153);
    a.insert(8675);
    a.insert(152);
    a.insert(10);
    a.erase(10);
    
    s.swap(a);
    assert(s.size() == 4);
    assert(a.size() == 5);
    
    assert(a.get(2, xx) && xx == 45);
    assert(s.get(3, xx) && xx == 8675);
    assert(!s.get(5, xx));
    assert(!s.get(-3, xx));
    
    assert(s.contains(634));
    assert(!s.contains(0));
    assert(a.contains(3));
    assert(!a.contains(78));
    
    Set d(a);
    assert(d.contains(3));
    assert(d.size() == 5);

    
    cout << "Passed all tests" << endl;
    return 0;
}
 */
 #include "newSet.h"
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

