//
//  main.cpp
//  Project_4
//
//  Created by Yunus Chang on 3/6/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//

#include <iostream>
#include "Trie.h"

struct b
{
    int a = 5;
};
int main(int argc, const char * argv[])
{
    Trie<int> tree;
    tree.insert("AAA", 42);
    tree.insert("AAA", 43);
    vector<int> vec = tree.find("AAA", true);
    cout << vec[0] << endl;
}
