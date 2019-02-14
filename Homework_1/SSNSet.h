//
//  SSNSet.hpp
//  Project_2
//
//  Created by Yunus Chang on 1/18/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//

#ifndef SSNSet_hpp
#define SSNSet_hpp

#include <stdio.h>
#include <iostream>

#include "Set.h"

using namespace std;

class SSNSet
{
public:
    SSNSet();          // Create an empty SSN set.
    
    bool add(unsigned long ssn);
    // Add an SSN to the SSNSet.  Return true if and only if the SSN
    // was actually added.
    
    int size() const;  // Return the number of SSNs in the SSNSet.
    
    void print() const;
    // Write every SSN in the SSNSet to cout exactly once, one per
    // line.  Write no other text.
    
    SSNSet& operator=(SSNSet &source);
    
private:
    Set m_set;
};

#endif /* SSNSet_hpp */
