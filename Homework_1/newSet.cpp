//
//  newSet.cpp
//  Project_2
//
//  Created by Yunus Chang on 1/18/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//

#include "newSet.h"

Set::Set()        // Create an empty set (i.e., one with no items).
{
    m_size = 0;
    m_totalCapacity = DEFAULT_MAX_ITEMS;
    m_item = new ItemType[DEFAULT_MAX_ITEMS];
}

Set::Set(int size)
{
    m_size = 0;
    m_totalCapacity = size;
    m_item = new ItemType[size];
}

Set::~Set()
{
    delete [] m_item;
}

bool Set::empty()  // Return true if the set is empty, otherwise false.
{
    if(m_size == 0)
    {
        return true;
    }
    return false;
}

int Set::size() const   // Return the number of items in the set.
{
    return m_size;
}

// Insert value into the set if it is not already present.  Return
// true if the value was actually inserted.  Leave the set unchanged
// and return false if the value was not inserted (perhaps because it
// was already in the set or because the set has a fixed capacity and
// is full).
bool Set::insert(const ItemType& value)
{
    if(m_size == m_totalCapacity)
        return false;
    for(int i = 0;i < m_size;i++)
    {
        if(value == m_item[i])
        {
            return false;
        }
    }
    m_item[m_size] = value;
    m_size++;
    return true;
}

// Remove the value from the set if present.  Return true if the
// value was removed; otherwise, leave the set unchanged and
// return false.
bool Set::erase(const ItemType& value)
{
    for(int i = 0;i < m_size;i++)
    {
        if(m_item[i] == value)
        {
            for(int j = i;j < m_size-1;j++)
            {
                m_item[j] = m_item[j+1];
            }
            m_size--;
            return true;
        }
    }
    return false;
}

    // Return true if the value is in the set, otherwise false.
bool Set::contains(const ItemType& value) const
{
    for(int i = 0;i < m_size;i++)
    {
        if(value == m_item[i])
        {
            return true;
        }
    }
    return false;
}

// If 0 <= i < size(), copy into value the item in the set that is
// strictly greater than exactly i items in the set and return true.
// Otherwise, leave value unchanged and return false.
bool Set::get(int i, ItemType& value) const
{
    if(i < 0 || i >= m_size)
    {
        return false;
    }
    for(int j = 0;j < m_size;j++)
    {
        int counter = 0;
        for(int k = 0;k < m_size; k++)
        {
            if(m_item[j] > m_item[k])
            counter++;
        }
        if(counter == i)
        {
        value = m_item[j];
        return true;
        }
    }
    return false;
}

// Exchange the contents of this set with the other one.
void Set::swap(Set& other)
{
    Set temp = *this;
    *this = other;
    other = temp;
}

Set& Set::operator= (const Set& source)
{
    delete [] m_item;
    m_item = new ItemType[source.m_totalCapacity];
    m_totalCapacity = source.m_totalCapacity;
    m_size = source.m_size;
    for(int i = 0;i < m_size;i++)
    {
        m_item[i] = source.m_item[i];
    }
    return *this;
}

Set::Set(const Set& source)
{
    m_item = new ItemType[source.m_totalCapacity];
    m_totalCapacity = source.m_totalCapacity;
    m_size = source.m_size;
    for(int i = 0;i < m_size;i++)
    {
        m_item[i] = source.m_item[i];
    }
}


