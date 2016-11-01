//
//  main.cpp
//  pGame
//
//  Created by Samuel Ang on 8/8/16.
//  Copyright (c) 2016 Samuel Ang. All rights reserved.
//
#include <stdlib.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <fstream>
#include "board.h"
#include <utility>
#include <vector>
#include "LpGenerator.h"
#include "glpk-4.60/src/glpk.h"
using std::pair;
using std::make_pair;
using std::cout;
using std::ifstream;
using std::getline;
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
    //Board m(w, h, tL, tP, ttl, aS, mt, gt, ttr);
    //m.printAllNodeInfo();
    
    //LpGenerator a(m);
    //a.convertToLp();
    
    //string inputFile = "lpFile.in";
    int width;
    int height;
    vector<pair<int, int>> targetLocations;
    pair<int,int> trueTargetLocation;
    vector<double> probDistribution;
    pair<int, int> attackerStart;
    vector<pair<pair<int,int>,pair<int,int>>> barriers;
    int moveCost;
    int predictionReward;
    int trueTargetReward;
    ifstream inFile;
    inFile.open("lpFile.in");
    string line;
    while(inFile >> line){
        if(line == "#width"){
            //cout << line << "|\n";
            inFile >> line;
            //cout << line << "||\n";
            width = atoi(line.c_str());
            //cout << width << "|||\n";
        }
        if(line == "#height"){
            inFile >> line;
            height = atoi(line.c_str());
            
        }
        //cout << "line: " <<line << "\n";
        if(line == "#target_locations"){
            inFile >> line;
            while(line.substr(0,1)!= "#"){
                int tlX = atoi(line.substr(0,1).c_str());
                int tlY = atoi(line.substr(2,1).c_str());
                //cout << "tlX " << tlX << "\n";
                targetLocations.push_back(make_pair(tlX,tlY));
                inFile >> line;
            }
            
        }
        if(line == "#probability_distribution"){
            inFile >> line;
            while(line.substr(0,1)!= "#"){
                double prob = atof(line.c_str());
                //cout << "prob: " << prob << "\n";
                probDistribution.push_back(prob);
                inFile >> line;
            }
        }
        if(line == "#barriers"){
            inFile >> line;
             while(line.substr(0,1)!= "#"){
                 cout << "wow\n";
                int bCord1x = atoi(line.substr(0,1).c_str());
                int bCord1y = atoi(line.substr(2,1).c_str());
                
                int bCord2x = atoi(line.substr(4,1).c_str());
                int bCord2y = atoi(line.substr(6,1).c_str());
                //cout << "tlX " << tlX << "\n";
                barriers.push_back(make_pair(make_pair(bCord1x,bCord1y),make_pair(bCord2x,bCord2y)));
                inFile >> line;
            }
        }
        if(line == "#true_target_location"){
            inFile >> line;
            int tlX = atoi(line.substr(0,1).c_str());
            int tlY = atoi(line.substr(2,1).c_str());
            trueTargetLocation = make_pair(tlX,tlY);
        }
        if(line == "#attacker_start"){
            inFile >> line;
            int attackerStartX = atoi(line.substr(0,1).c_str());
            int attackerStartY = atoi(line.substr(2,1).c_str());
            attackerStart = make_pair(attackerStartX, attackerStartY);
        }
        if(line == "#move_cost"){
            inFile >> line;
            moveCost = atoi(line.c_str());
        }
        if(line =="#prediction_reward"){
            inFile >> line;
            predictionReward = atoi(line.c_str());
        }
        if(line =="#true_target_reward"){
            inFile >> line;
            trueTargetReward = atoi(line.c_str());
        }
    }
    
    cout << barriers.size() << " is the b size\n";
    for(auto x : barriers){
        //cout << x.first.first << "," << x.first.second << ";" << x.second.first << "," << x.second.second << "\n";
    }
    Board m(width, height, targetLocations, probDistribution, trueTargetLocation, attackerStart, moveCost, predictionReward, trueTargetReward, barriers);
    //Board m(width, height, targetLocations, probDistribution, trueTargetLocation, attackerStart, moveCost, predictionReward, trueTargetReward);
    m.printAllNodeInfo();
    
    LpGenerator a(m);
    a.convertToLp();
    //cout << width;
    return 0;
}
