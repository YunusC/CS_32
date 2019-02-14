//
//  main.cpp
//  Project_2
//
//  Created by Yunus Chang on 1/23/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//

#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

#include <type_traits>

#define CHECKTYPE(f, t) { auto p = static_cast<t>(f); (void)p; }

static_assert(std::is_default_constructible<Set>::value,
              "Set must be default-constructible.");
static_assert(std::is_copy_constructible<Set>::value,
              "Set must be copy-constructible.");

void thisFunctionWillNeverBeCalled()
{
    CHECKTYPE(&Set::operator=, Set& (Set::*)(const Set&));
    CHECKTYPE(&Set::empty,     bool (Set::*)() const);
    CHECKTYPE(&Set::size,      int  (Set::*)() const);
    CHECKTYPE(&Set::insert,    bool (Set::*)(const ItemType&));
    CHECKTYPE(&Set::erase,     bool (Set::*)(const ItemType&));
    CHECKTYPE(&Set::contains,  bool (Set::*)(const ItemType&) const);
    CHECKTYPE(&Set::get,       bool (Set::*)(int, ItemType&) const);
    CHECKTYPE(&Set::swap,      void (Set::*)(Set&));
    CHECKTYPE(unite,    void (*)(const Set&, const Set&, Set&));
    CHECKTYPE(subtract, void (*)(const Set&, const Set&, Set&));
}

 void test() //test std::strings
{
    Set ss;
    assert(ss.insert("roti")); //check insert
    assert(ss.insert("pita"));
    assert(ss.size() == 2); //check size
    assert(ss.contains("pita"));//check contains
    ItemType x = "laobing";
    assert(ss.get(0, x)  &&  x == "pita"); //check get
    assert(ss.get(1, x)  &&  x == "roti"); //check get
    
    Set s;
}

 void a() //test std::strings
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
    cout << ss.size() << endl;
    assert(ss.empty());
    cout << "Passed all tests" << endl;
}

void b()
{
    Set ss;
    assert(ss.empty());
    ss.insert("lavash");
    ss.insert("roti");
    ss.insert("chapati");
    
    Set s;
    s.insert("injera");
    s.insert("rotis");
    s.insert("matzo");
    s.insert("injeras");
    
    Set x;
    unite(ss,s,x);
    x.dump();
    
    Set a;
    a.insert("lavash");
    a.insert("roti");
    a.insert("chapati");
    a.swap(a); //check swap when both parameters are equal
    assert(a.size() == 3);
    
    a = a; //check assignment operator when both original and source are the same Set
    assert(a.size() == 3);
}

/*
void testULS() //test unsigned long
{
    Set uls;
    assert(uls.insert(10)); //check insert
    assert(uls.insert(20)); //check insert
    assert(uls.size() == 2); //check size
    assert(uls.contains(20)); //check contains
    
    Set s;
    assert(s.empty()); //check empty
    assert(s.insert(1)); //check insert
    assert(!s.insert(1)); //check insert if value already exists in list
    assert(s.insert(2));
    assert(s.insert(3));
    assert(s.insert(4));
    assert(s.size() == 4); //check size
    ItemType y = 55;
    assert(s.get(2,y) && y == 3); //check get
    assert(!s.get(4,y) && y == 3); //check get with out of scope parameter
    
    s.swap(uls);
    s.swap(uls);
    
    ItemType x = 30;
    assert(uls.get(0, x)  &&  x == 10); //check get
    assert(uls.get(1, x)  &&  x == 20);
    assert(!uls.get(2, x)  &&  x == 20); //check get with out of scope parameter
    
    Set a;
    assert(a.empty()); //check empty
    assert(a.insert(1)); //check insert
    assert(a.erase(1)); //check erase
    assert(a.empty()); //check empty
    assert(a.insert(2)); //check insert
    assert(a.contains(2)); //check contains
    
    Set b, c; //check swap on empty sets
    b.swap(c);
    c.swap(b);
    
    assert(b.insert(1));
    assert(b.insert(2));
    assert(b.insert(3));
    assert(b.insert(4));
    assert(b.insert(5));
    assert(b.size()==5);
    
    assert(c.insert(2));
    assert(c.insert(3));
    assert(c.size()==2);
    
    subtract(b,c,b); //check subtract when s1 and result are the same
    b.dump();
    assert(b.size()==3);
    
    unite(b,c,c); //check unite when s2 and result are the same
    c.dump();
    assert(c.size()==5);
    
    unite(c,c,c); //check unite when all parameters are the same
    c.dump();
    assert(c.size()==5);
    
    subtract(c,c,c); //check subtract when all parameters are the same
    c.dump();
    assert(c.size()==0);
}
*/

int main()
{
    test();
    a();
    b();
    //testULS();
    cerr << "Passed all tests" << endl;
}
