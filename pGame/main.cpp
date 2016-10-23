//
//  main.cpp
//  pGame
//
//  Created by Samuel Ang on 8/8/16.
//  Copyright (c) 2016 Samuel Ang. All rights reserved.
//

#include <iostream>
#include "board.h"
#include <utility>
#include <vector>
#include "LpGenerator.h"
#include "glpk-4.60/src/glpk.h"
using std::pair;
using std::make_pair;
using std::cout;
int main(int argc, const char * argv[]) {
    //Board(int width, int height, vector<pair<int,int>> targetLocs, vector<double> targetProbs, pair<int, int> trueTargetLoc, pair<int, int> attackerStart, double mt, double gt, double ttr)
    int w = 3;
    int h = 1;
    vector<pair<int, int>> tL;
    tL.push_back(make_pair(0,0));
    tL.push_back(make_pair(0,2));
    
    vector<double> tP;
    tP.push_back(.5);
    tP.push_back(.5);
    
    pair<int, int> ttl = make_pair(0,2);
    pair<int, int> aS = make_pair(0,1);
    
    double mt = 1;
    double gt = 1;
    double ttr = 3;
    
    //[.5T]---[Start]---[.5F]
    Board m(w, h, tL, tP, ttl, aS, mt, gt, ttr);
    m.printAllNodeInfo();
    
    LpGenerator a(m);
    a.convertToLp();
    
    return 0;
}
