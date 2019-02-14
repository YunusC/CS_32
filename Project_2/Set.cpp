//
//  Set.cpp
//  Project_2
//
//  Created by Yunus Chang on 1/23/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//

#include "Set.h"

Set::Set()//m_prev points to &m_dummy so that future functions do not have to treat the head node case differently
{
    m_dummy.m_next = nullptr;
    m_dummy.m_prev = &m_dummy;
}

Set::Set(const Set& source)
{
    copy(source);
}

Set& Set::operator=(const Set& source)
{
    if(this == &source) //if the two Sets are the same set
    {
        return *this; //return the Set as it is
    }
    destruct();
    copy(source);
    return *this;
}

Set::~Set()
{
    destruct();
}

bool Set::empty() const
{
    if(m_dummy.m_next == nullptr)//if the head pointer doesn't point to an item, return true
    {
        return true;
    }
    return false;
}

int Set::size() const
{
    int counter = 0;
    Item* x = m_dummy.m_next;
    while(x != nullptr) //repeatedly increment counter until we point at nothing
    {
        counter++;
        x = x->m_next;
    }
    return counter;
}
bool Set::insert(const ItemType& value)
{
    Item* x = m_dummy.m_next;
    while(x != nullptr) //repeatedly iterate through the list
    {
        if(x->m_item == value)//if the value already exists in the list, exit
            return false;
        x = x->m_next;
    }
    tailInsert(value); //if not, then insert the value into the end of the list
    return true;
}

bool Set::erase(const ItemType& value)
{
    Item* x = m_dummy.m_next;
    while(x != nullptr) //repeatedly iterate through the list
    {
        if(x->m_item == value) //if we find the item
        {
        
            if(x->m_prev == nullptr) //if the item is the first in the list
            {
                m_dummy.m_next = x->m_next; //set the head pointer to the item that the chosen item pointed to
            }
            else //if item is not first in the list
            {
                x->m_prev->m_next = x->m_next; //set the next pointer of the previous item to the item after the chosen item
            }
            if(x->m_next == nullptr) //if item is last in the list
            {
                m_dummy.m_prev = x->m_prev; //set the tail pointer of the list to the item before the chosen item
                if(x->m_prev == nullptr) //if the item is the last and first item in the list(the only item)
                {
                    m_dummy.m_prev = &m_dummy; //set the tail pointer pointing to the dummy Item object itself
                }
            }
            else //if the item is not last in the list
            {
                x->m_next->m_prev = x->m_prev; //set the prev pointer of the next item to the prev pointer of the chosen item
            }
            delete x; //then delete x
            return true; //exit
        }
        x = x->m_next;
    }
    return false;
}

bool Set::contains(const ItemType& value) const
{
    Item* x = m_dummy.m_next;
    while(x != nullptr) //repeatedly iterate through list
    {
        if(x->m_item == value) //if value is found
            return true; //return true
        x = x->m_next;
    }
    return false; //if not then return false
}

bool Set::get(int pos, ItemType& value) const
{
    int counter;
    Item* x = m_dummy.m_next;
    Item* y = nullptr;
    while(x != nullptr) //repeatedly iterate through list
    {
        counter = 0; //create a counter varialbe equal to zero
        y = m_dummy.m_next;
        while(y != nullptr) //repeatedly iterate through list again
        {
            if(x->m_item > y->m_item) //if a value is less than the chosen value
                counter++; //increment the counter
            y = y->m_next;
        }
        if(counter == pos) //if the given item had "pos" items less than it in the list
        {
            value = x->m_item; //set the value to the chosen value
            return true; //return true
        }
        x = x->m_next;
    }
    return false;
}

void Set::swap(Set& other)
{
    Set temp = *this;
    *this = other;
    other = *this;
}

void Set::dump() const
{
    print();
}

void Set::tailInsert(const ItemType& value)
{
    Item* x = new Item; //create a new Item
    x->m_prev = m_dummy.m_prev; //link the prev pointer of the new Item to the item the tail pointer points to
    if(x->m_prev == &m_dummy) //if it is the first item in the list
    {
        x->m_prev = nullptr; //set the prev pointer of the new Item to a nullptr
    }
    m_dummy.m_prev->m_next = x; //set the next pointer of the last Item in the list to the new Item
    m_dummy.m_prev = x; //set the tail pointer to the new Item
    x->m_next = nullptr; //set the next pointer of the new Item to nullptr
    x->m_item = value; //assign the given value to the new Item
}

bool Set::itemAtPos(int pos, ItemType& value) const
{
    int counter = 0;
    if(pos < 0)
        return false;
    Item* x = m_dummy.m_next;
    while(x != nullptr)
    {
        if(counter == pos)
        {
            value = x->m_item;
            return true;
        }
        x = x->m_next;
    }
    return false;
}

void Set::print() const
{
    Item* x = m_dummy.m_next;
    while(x != nullptr)
    {
        cerr << x->m_item << " ";
        x = x->m_next;
    }
    cerr << endl;
}

void Set::copy(const Set& source)
{
    m_dummy.m_next = nullptr;
    m_dummy.m_prev = &m_dummy;
    if(source.empty())//if the source set is empty, exit out of function
    {
        return;
    }
    Item* x = source.m_dummy.m_next;
    while(x != nullptr)//iterate through the linked list
    {
        tailInsert(x->m_item); //insert every item from the source set into the new set
        x = x->m_next;
    }
}

void Set::destruct()
{
    Item* x = m_dummy.m_next;
    Item* y = nullptr;
    while(x != nullptr) //iterate through the list
    {
        y = x; //done so the I can delete the current item while having the value of the next item
        x = x->m_next;
        delete y; //delete every item in the list
    }
}

void unite(const Set& s1, const Set& s2, Set& result)
{
    Set temp(s1); //create a temp Set equal to s1
    ItemType x;
    for(int i = 0;i < s2.size();i++) //iterate through Set s2
    {
        if(s2.get(i,x)) //insert each item from s2 into temp unless the value already exists in temp
        {
            temp.insert(x);
        }
    }
    result = temp; //set result equal to temp
}

void subtract(const Set& s1, const Set& s2, Set& result)
{
    Set temp(s1); //create a temp Set equal to s1
    ItemType x;
    for(int i = 0;i < s2.size();i++) //iterate through Set s2
    {
        if(s2.get(i,x))
        {
            temp.erase(x); //erase every item in s2 from temp
        }
    }
    result = temp; //set result equal to temp
}
