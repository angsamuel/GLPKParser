//
//  attacker.h
//  pGame
//
//  Created by Samuel Ang on 8/16/16.
//  Copyright (c) 2016 Samuel Ang. All rights reserved.
//

#ifndef pGame_attacker_h
#define pGame_attacker_h
#include "board.h"
#include <stdio.h>
#include <stdlib.h>
//#include <glpk.h>
#include <vector>
class Attacker{
private:
    Board gameBoard;
public:
    Attacker(){}
    Attacker(Board &b){
        gameBoard = b;
    }
    
    int getCeling();
    
};

#endif
