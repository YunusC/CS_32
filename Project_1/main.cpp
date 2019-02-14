//
//  main.cpp
//  Project_1
//
//  Created by Yunus Chang on 1/9/19.
//  Copyright © 2019 Yunus Chang. All rights reserved.
//

// zombies.cpp


#include "globals.h"
#include "Zombie.h"
#include "Player.h"
#include "Arena.h"
#include "Game.h"


int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(20, 30, 10);
    
    // Play the game
    g.play();
}


