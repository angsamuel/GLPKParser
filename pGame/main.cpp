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
using std::to_string;
int main(int argc, const char * argv[]) {
    //Board(int width, int height, vector<pair<int,int>> targetLocs, vector<double> targetProbs, pair<int, int> trueTargetLoc, pair<int, int> attackerStart, double mt, double gt, double ttr)
    vector<pair<int, int>> tL;
    tL.push_back(make_pair(0,0));
    tL.push_back(make_pair(0,2));
    
    

    
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
    vector<int> barrierValues;
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
            if(line == "bruteforce"){
                cout << "we got bruteforce boys\n";
                for(int i = 0; i<height; ++i){
                    for(int j = 0; j<width; ++j){
                    barriers.clear();
                        string myFileString = "";
                        if(i>0){
                            barriers.push_back(make_pair(make_pair(i,j),make_pair(i-1,j)));
                            barriers.push_back(make_pair(make_pair(i-1,j), make_pair(i,j)));
                            myFileString = "lpFiles/lpFile" + to_string(i) + "u" + to_string(j) + "a" + to_string(i-1) + "u" + to_string(j) + ".lp";
                            cout << myFileString << "\n";
                            Board m(width, height, targetLocations, probDistribution, trueTargetLocation, attackerStart, moveCost, predictionReward, trueTargetReward, barriers, myFileString, barrierValues);
                            LpGenerator a(m);
                            a.convertToLp();
                            m.printBoard();
                            barriers.clear();
                        }
                        if(j>0){
                            barriers.push_back(make_pair(make_pair(i,j),make_pair(i,j-1)));
                            barriers.push_back(make_pair(make_pair(i,j-1), make_pair(i,j)));
                            myFileString = "lpFiles/lpFile" + to_string(i) + "u" + to_string(j) + "a" + to_string(i) + "u" + to_string(j-1) + ".lp";
                            cout << myFileString << "\n";
                            Board m2(width, height, targetLocations, probDistribution, trueTargetLocation, attackerStart, moveCost, predictionReward, trueTargetReward, barriers, myFileString, barrierValues);
                            LpGenerator a2(m2);
                            a2.convertToLp();
                            m2.printBoard();
                            barriers.clear();
                        }
                    }
                }
                barriers.clear();
            }else{
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
                    barrierValues.push_back(vect.at(4));
                    inFile >> line;
            }
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
    
    //cout << barriers.size() << " is the b size\n";
    for(auto x : barriers){
        //cout << x.first.first << "," << x.first.second << ";" << x.second.first << "," << x.second.second << "\n";
    }
    string fileString = "lpFiles/default.lp";
    Board m(width, height, targetLocations, probDistribution, trueTargetLocation, attackerStart, moveCost, predictionReward, trueTargetReward, barriers, fileString, barrierValues);
    m.printBoard();
    //Board m(width, height, targetLocations, probDistribution, trueTargetLocation, attackerStart, moveCost, predictionReward, trueTargetReward);
    //m.printAllNodeInfo();
    
    LpGenerator a(m);
    a.convertToLp();
    //cout << width;
    //cout << "execution completed\n";
    return 0;
}

/*Bash
 
 #/bin/bash
 clear
 for C in *.lp; do count=$((count+1)); done
 
 echo "processing lp files..."
 sleep 3
 for X in *.lp; do
 output=$(echo $X | cut -f 1 -d '.')
 glpsol --cpxlp $X -o $output.out --interior --log tsp.log > dev/null
 fileProgress=$((fileProgress+1))
 clear
 echo -e "completed" "${fileProgress}" "/" "${count}" "files"
 done
 echo "process complete :^)"

 
 
 
 */
