//
//  attacker.h
//  pGame
//
//  Created by Samuel Ang on 8/16/16.
//  Copyright (c) 2016 Samuel Ang. All rights reserved.
//

#ifndef pGame_LpGenerator_h
#define pGame_LpGenerator_h
#include "board.h"
#include <stdio.h>
#include <stdlib.h>
//#include <glpk.h>
#include <vector>
class LpGenerator{
private:
    Board gameBoard;
public:
    LpGenerator(){}
    LpGenerator(Board &b){
        gameBoard = b;
    }
    
    int getCeling();
    void writeConstraints(Board& gameBoard, std::ofstream lpFile);
    void convertToLp();
    string createLpVar(string pre, pair<int, int> assumedTarget, pair<int, int> state);
    
};

#endif
