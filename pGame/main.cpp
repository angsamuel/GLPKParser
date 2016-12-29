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

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using std::pair;
using std::make_pair;
using std::cout;
using std::ifstream;
using std::getline;
using std::stringstream;
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
        if(line == "#columns"){
            inFile >> line;
            width = atoi(line.c_str());
        }
        if(line == "#rows"){
            inFile >> line;
            height = atoi(line.c_str());
        }
        if(line == "#target_locations"){
            /*
            while(line.substr(0,1)!= "#"){
             
                inFile >> line;
             
                inFile >> line;
            }
            cout << "target locations size: "targetLocations.size() << std::endl;*/
            
            
            inFile >> line;
            while(line.substr(0,1)!= "#"){
                int i;
                vector<int> vect;
                stringstream ss(line);
                while(ss>>i){
                    vect.push_back(i);
                    if(ss.peek() == ' ' || ss.peek() == ','){ss.ignore();}
                }
                targetLocations.push_back(make_pair(vect.at(0),vect.at(1)));
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
                int i;
                vector<int> vect;
                stringstream ss(line);
                while(ss>>i){
                    vect.push_back(i);
                    if(ss.peek() == ' ' || ss.peek() == ','){ss.ignore();}
                    if(ss.peek() == ';'){
                        ss.ignore();
                    }
                }
                cout << vect.size() << std::endl;
                cout << vect.at(0) << ", " << vect.at(1) << std::endl;
                cout << vect.at(2) << ", " << vect.at(3) << std::endl;
                barriers.push_back(make_pair(make_pair(vect.at(0),vect.at(1)),make_pair(vect.at(2),vect.at(3))));
                inFile >> line;
            }
            
        }
        if(line == "#true_target_location"){
            inFile >> line;
            //int tlX = atoi(line.substr(0,1).c_str());
            //int tlY = atoi(line.substr(2,1).c_str());
            int i;
            vector<int> vect;
            stringstream ss(line);
            while(ss>>i){
                vect.push_back(i);
                if(ss.peek() == ' ' || ss.peek() == ','){ss.ignore();}
            }
            trueTargetLocation = make_pair(vect.at(0),vect.at(1));
        }
        if(line == "#attacker_start"){
            inFile >> line;
            //int tlX = atoi(line.substr(0,1).c_str());
            //int tlY = atoi(line.substr(2,1).c_str());
            int i;
            vector<int> vect;
            stringstream ss(line);
            while(ss>>i){
                vect.push_back(i);
                if(ss.peek() == ' ' || ss.peek() == ','){ss.ignore();}
            }
            attackerStart = make_pair(vect.at(0),vect.at(1));
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
    //m.printAllNodeInfo();
    
    LpGenerator a(m);
    a.convertToLp();
    //cout << width;
    cout << "execution completed\n";
    return 0;
}
