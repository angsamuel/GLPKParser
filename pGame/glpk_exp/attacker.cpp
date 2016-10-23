//
//  attacker.cpp
//  pGame
//
//  Created by Samuel Ang on 8/18/16.
//  Copyright (c) 2016 Samuel Ang. All rights reserved.
//

#include "attacker.h"
#include <cmath>
#include <stdlib.h>     /* abs */
int Attacker::getCeling(){
    
    //shortest path only works for unobstructed rectangular grids currently
    //a more complete version can be written in later
    int firstDif = abs(gameBoard.getAtStart().first - gameBoard.getTrueTargetLoc().first);
    int secDif = abs(gameBoard.getAtStart().second - gameBoard.getTrueTargetLoc().second);
    int distance = (firstDif + secDif);
    //cout << "distance: " << distance << "\n";
    
    //cout << "\nGUESS TAX: " << gameBoard.getGuessTax() << "\n";
    //cout << "\nMOVETAX: " << gameBoard.getMoveTax() << "\n";
    //cout << "\nDISTANCE: " << distance << "\n";
    int worstCaseShortestPath = (distance * gameBoard.getGuessTax())+(distance * gameBoard.getMoveTax());
    //cout << "wcsp: " << worstCaseShortestPath << "\n";
    int movesCeling = worstCaseShortestPath/gameBoard.getMoveTax();
    
    return movesCeling;
}