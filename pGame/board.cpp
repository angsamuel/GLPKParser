//
//  board.cpp
//  pGame
//
//  Created by Samuel Ang on 8/8/16.
//  Copyright (c) 2016 Samuel Ang. All rights reserved.
//
/*
 implement finding correct boundaries,
 implement brute force solution and attempt to find optimal solution
 extrapolate information,
 implement faster solution, and compare with brute force answers
*/
#include <iostream>
#include "board.h"
#include <algorithm>
#include <utility>
using std::to_string;
using std::pair;
using std::make_pair;
using std::cout;
using std::find;
//STRATEGY EVALUATION-----------------------------------------------------------------------
//check to see if strategy is valid
bool Board::validAStrat(vector<pair<int, int>> attackerStrategy){
    //make sure the attacker moved in the first place
    if(attackerStrategy.size()<1){
        return false;
    }
    //check to see if the strategy ends at the true target
    if(attackerStrategy.at(attackerStrategy.size()-1) != trueTarget){
        return false;
    }
    //check to see if starting move is valid
    auto m = &nodes.at((attackerStrategy.at(1).first)).at((attackerStrategy.at(1).second));
    Node s = nodes.at(atStart.first).at(atStart.second);
    if(!(find(s.connections.begin(), s.connections.end(), m)!=s.connections.end())){
        return false;
    }
    //check to see that moves follow each other
    for(int x=1; x<attackerStrategy.size(); ++x){
        Node prevMove = nodes.at((attackerStrategy.at(x-1)).first).at((attackerStrategy.at(x-1)).second);
        auto curMove = &nodes.at((attackerStrategy.at(x)).first).at((attackerStrategy.at(x)).second);
        if(!(find(prevMove.connections.begin(), prevMove.connections.end(), curMove)!=prevMove.connections.end())){
            return false;
        }
    }
    return true;
}
//evaluate attacker strategy
double Board::evalAStrat(vector<pair<int, int>> aStrat){
    int score = 0;
    if(validAStrat(aStrat)){
        score = int(trueTargetReward) - int(moveTax*aStrat.size());
    }
    return score;
}
//return the value of the defender's strategy
double Board::evalDStrat(vector<pair<int,int>> dStrat){
    double score = 0;
    for(auto x : dStrat){
        if (x == trueTarget){
            score += guessTax;
        }
    }
    return score;
}
//PRINTING NODE INFORMATION-----------------------------------------------------------------
//print the details of a Node at a given location
void Board::printNode(pair<int,int> location){
    cout << "information for node at (" << (location).first << ", " << (location).second << ")\n";
    cout << "---\n";
    cout << "node address: " << &nodes.at((location).first).at((location).second) << "\n";
    cout << "node is target: " << nodes.at((location).first).at((location).second).isTarget << "\n";
    cout << "node is the true target: " << nodes.at((location).first).at((location).second).isTrueTarget << "\n";
    cout << "connections---\n";
    for(auto x : nodes.at((location).first).at((location).second).connections){
        cout << x << "\n";
    }
    cout << "\nend of info\n";
    cout << "---\n\n";
}
//prints info for every node
void Board::printAllNodeInfo(){
    for(int i = 0; i<height; ++i){
        for(int j = 0; j<width; ++j){
            auto x = make_pair(i,j);
            printNode(x);
        }
    }
}
//GET FUNCTIONS-----------------------------------------------------------------------------
pair<int,int> Board::getTrueTargetLoc(){
    return trueTarget;
}
vector<pair<int,int>> Board::getTargetLocs(){
    return targets;
}
vector<pair<int, int>> Board::getTargets(){
    return targets;
}
double Board::getTargetProb(pair<int, int> p ){
    return nodes.at(p.first).at(p.second).probability;
}
double Board::getMoveTax(){
    return moveTax;
}
double Board::getGuessTax(){
    return guessTax;
}
pair<int,int> Board::getAtStart(){
    return atStart;
}
double Board::getTrueTargetReward(){
    return trueTargetReward;
}
int Board::getWidth(){
    return width;
}
int Board::getHeight(){
    return height;
}
vector<pair<pair<int,int>,pair<int,int>>> Board::getBarriers(){
    return barriers;
}
vector<int> Board::getBarrierValues(){
    return barrierValues;
}
//SET FUNCTIONS------------------------------------------------------------------------------
//change the true target location
void Board::setTrueTargetLoc(pair<int,int> loc){
    nodes.at(trueTarget.first).at(trueTarget.second).isTrueTarget = false;
    nodes.at(loc.first).at(loc.second).isTrueTarget = true;
    trueTarget = loc;
}
//add a target location
void Board::setTargetLoc(pair<int,int> loc){
    nodes.at(loc.first).at(loc.second).isTarget = true;
}
//removes, target marker. will not remove the *true* target Node marker
void Board::removeTargetLoc(pair<int, int> loc){
    if(loc!=trueTarget){
        nodes.at(loc.first).at(loc.second).isTarget = 0;
    }
}
//set move and guess tax
void Board::setMoveTax(double a){
    moveTax = a;
}
void Board::setGuessTax(double b){
    guessTax = b;
}
//set attacker's starting location
void Board::setAtStart(pair<int,int> loc){
    atStart = loc;
}
//HELPER FUNCTIONS----------------------------------------------------------------------------
//reward function
double Board::reward(pair<int, int> attackerLocation, pair<int, int> i, pair<int, int> j, pair<int, int> theta){
    if(j!=theta && i!=theta){
        return moveTax;
    }else if(j!=theta && i==theta){
        return moveTax+guessTax;
    }else if(j==theta && i!=theta){
        return moveTax - trueTargetReward;
    }else if(j==theta && i==theta){
        return moveTax + guessTax - trueTargetReward;
    }
    std::cerr << "Error, a paradox has occured.\n";
    return 0;
}

vector<pair<int,int>> Board::getConnectionsOfNode(pair<int,int> loc){
    vector<pair<int, int>> connectionCoords;
    for(auto x : nodes.at(loc.first).at(loc.second).connections){
        connectionCoords.push_back(make_pair(x->rCoord, x->cCoord));
    }
    return connectionCoords;
}

//quick function that returns true if the node at the given location is a potential target
bool Board::isNodeATarget(pair<int, int> loc){
    return nodes.at(loc.first).at(loc.second).isTarget;
}

//print the board
void Board::printBoard(){
    cout << "   ";
    for(int i = 0; i<width; ++i){
        cout << i << " ";
    }
    cout << "\n\n";
    for(int i = 0; i<height; ++i){
        cout << i << "  ";
        for(int j = 0; j<width; j++){
            if(nodes.at(i).at(j).isTarget){
                cout << "T";
            }else if(i==atStart.first && j==atStart.second){
                cout << "A";
            }else{
                cout << "O";
            }
            bool printedConnection = false;
            for(auto c : nodes.at(i).at(j).connections){
                if(c->rCoord == i && c->cCoord == j+1){
                   cout << "-";
                    printedConnection = true;
                }
            }
            if(!printedConnection){cout << " ";}
        }
        cout << "\n";
        //vertical connection
        cout << "   ";
        for(int j = 0; j<width; j++){
            cout << "";
            bool printedConnection = false;
            for(auto c : nodes.at(i).at(j).connections){
                if(c->rCoord == i+1 && c->cCoord == j){
                    cout << "| ";
                    printedConnection = true;
                    
                }
            }
            if(!printedConnection){cout << "  ";}
        }
        cout << "\n";
    }
}