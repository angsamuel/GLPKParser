//
//  board.cpp
//  pGame
//
//  Created by Samuel Ang on 8/8/16.
//  Copyright (c) 2016 Samuel Ang. All rights reserved.
//

#include <iostream>
#include "board.h"
#include <algorithm>
#include <utility>
using std::pair;
using std::make_pair;
using std::cout;
using std::find;
bool Board::validAStrat(vector<pair<int, int> > attackerStrategy){
    //check to see if strategy exists
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

//return the value of the attacker's strategy
int Board::evalAStrat(vector<pair<int, int> > aStrat){
    int score = 0;
    if(validAStrat(aStrat)){
        score = int(trueTargetReward) - int(moveTax*aStrat.size());
    }
    return score;
}

//return the value of the defender's strategy
int Board::evalDStrat(vector<pair<int,int> > dStrat){
    int score = 0;
    for(auto x : dStrat){
        if (x == trueTarget){
            score += guessTax;
        }
    }
    return score;
}

//prints info for every node
void Board::printAllNodeInfo(){
    for(int i = 0; i<3; ++i){
        for(int j = 0; j<3; ++j){
            auto x = make_pair(i,j);
            printNode(x);
        }
    }
}

//print connections and other info on the specified node
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

pair<int,int> Board::getTrueTargetLoc(){
    return trueTarget;
}

vector<pair<int,int> > Board::getTargetLocs(){
    return targets;
}

pair<int,int> Board::getAtStart(){
    return atStart;
}

int Board::getGuessTax(){
    return guessTax;
}

int Board::getMoveTax(){
    return moveTax;
}

void Board::setAtStart(pair<int,int> loc){
    atStart = loc;
}

void Board::setGuessTax(int b){
    guessTax = b;
}

void Board::setMoveTax(int a){
    moveTax = a;
}

void Board::setTargetLoc(pair<int,int> loc){
    nodes.at(loc.first).at(loc.second).isTarget = true;
}

void Board::setTrueTargetLoc(pair<int,int> loc){
    nodes.at(trueTarget.first).at(trueTarget.second).isTrueTarget = false;
    nodes.at(loc.first).at(loc.second).isTrueTarget = true;
    trueTarget = loc;
}

//will not remove the true target Node
void Board::removeTargetLoc(pair<int, int> loc){
    if(loc!=trueTarget){
        nodes.at(loc.first).at(loc.second).isTarget = 0;
    }
}






