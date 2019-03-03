//
//  list.cpp
//  Homework_4
//
//  Created by Yunus Chang on 3/2/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//

#include "list.h"

void listAll(const MenuItem* m, string path) // two-parameter overload
{
    if(m->name() != "")
        cout << path + m->name() << endl;
    if(m->menuItems() == nullptr)
    {
        return;
    }
    else
    {
        if(m->name() != "")
            path = path + m->name() + '/';
        for(int i = 0;i < m->menuItems()->size();i++)
        {
            listAll((*(m->menuItems()))[i], path);
        }
    }
}

