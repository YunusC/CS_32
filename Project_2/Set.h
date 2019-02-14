//
//  Set.hpp
//  Project_2
//
//  Created by Yunus Chang on 1/23/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//

#ifndef Set_hpp
#define Set_hpp

#include <stdio.h>
#include <string>
#include <iostream>

using ItemType = std::string;
//using ItemType = unsigned long;
using namespace std;

class Set
{
public:
    Set();
    Set(const Set&);
    Set& operator=(const Set&);
    ~Set();
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    void swap(Set& other);
    void dump() const; //get rid of this
private:
    void tailInsert(const ItemType& value);
    void copy(const Set&);
    void destruct();
    bool itemAtPos(int pos, ItemType& value) const;
    void print() const;
    struct Item
    {
        ItemType m_item;
        Item* m_next;
        Item* m_prev;
    };
    Item m_dummy;
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif /* Set_hpp */
