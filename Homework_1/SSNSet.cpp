//
//  SSNSet.cpp
//  Project_2
//
//  Created by Yunus Chang on 1/18/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//

#include "SSNSet.h"

SSNSet::SSNSet()        // Create an empty SSN set.
{
    
}

// Add an SSN to the SSNSet.  Return true if and only if the SSN
// was actually added.
bool SSNSet::add(unsigned long ssn)
{
    return m_set.insert(ssn);
}

int SSNSet::size() const  // Return the number of SSNs in the SSNSet.
{
    return m_set.size();
}

// Write every SSN in the SSNSet to cout exactly once, one per
// line.  Write no other text.
void SSNSet::print() const
{
    ItemType temp;
    for(int i = 0;i < m_set.size();i++)
    {
        m_set.get(i,temp);
        cout << temp << endl;
    }
}

