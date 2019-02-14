//
//  Game.hpp
//  Project_1
//
//  Created by Yunus Chang on 1/9/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
};
#endif /* Game_hpp */
