//
//  board.h
//  pGame
//
//  Created by Samuel Ang on 8/8/16.
//  Copyright (c) 2016 Samuel Ang. All rights reserved.
//

#ifndef __pGame__board__
#define __pGame__board__
#include <stdio.h>
#include <vector>
#include <utility>
#include <iostream>
using std::cout;
using std::pair;
using std::make_pair;
using std::vector;
using std::get;
class Board{
private:
    struct Node{
        vector<Node*> connections;
        bool isTarget;
        bool isTrueTarget;
        //makes node identical but other nodes will not contain connections
        Node &operator=(const Node &other){
            connections = other.connections;
            return *this;
        }
        bool operator==(const Node &other) const {
            if(connections == other.connections){
                if(isTarget==other.isTarget) {
                    return isTrueTarget==other.isTrueTarget;
                }
            }
            return false;
        }
        bool operator!=(const Node &other) const { return !(*this == other); }
    };
    //2D vector of nodes
    vector<vector<Node> > nodes;
    
    //list of target locations
    vector<pair<int,int> > targets;
    
    //location of attacker's intended target
    pair<int,int> trueTarget;
    
    //attacker's starting location
    pair<int,int> atStart;
    
    //attacker's penalty for moving
    int moveTax;
    
    //defender's reward for correct prediction
    int guessTax;
    
    //reward for reaching the true target
    int trueTargetReward;
public:
    Board(){}
    Board(int width, int height, vector<pair<int,int> > targetLocs, pair<int, int> trueTargetLoc, pair<int, int> attackerStart, int mt, int gt, int ttr){
        moveTax = mt;
        guessTax = gt;
        trueTargetReward = ttr;
        //fill 2D Vector with empty Nodes
        vector<Node> row;
        for(int j=0; j<width; ++j){
            Node tempNode;
            row.push_back(tempNode);
        }
        for(int i=0; i<height; ++i){
            nodes.push_back(row);
        }
        
        //establish connections
        for(int i=0; i<height; ++i){
            for(int j=0; j<width; ++j){
                //cout << "connection for: " << &nodes.at(i).at(j) << "\n";
                if(i>0){nodes.at(i).at(j).connections.push_back(&nodes.at(i-1).at(j));}
                if(j>0){nodes.at(i).at(j).connections.push_back(&nodes.at(i).at(j-1));}
                if(i<height-1){nodes.at(i).at(j).connections.push_back(&nodes.at(i+1).at(j));}
                if(j<width-1){nodes.at(i).at(j).connections.push_back(&nodes.at(i).at(j+1));}
            }
        }
        
        //set target identifier to false
        for(int i = 0; i<height; ++i){
            for(auto x : nodes.at(i)){
                x.isTarget = false;
                x.isTrueTarget = false;
            }
        }
        
        //create vector of targets, set target node identifiers to true
        targets = targetLocs;
        for(int x=0; x<targetLocs.size(); ++x){
            
            nodes.at((targetLocs.at(x)).first).at((targetLocs.at(x)).second).isTarget = true;
        }
        trueTarget = trueTargetLoc;
        nodes.at(trueTargetLoc.first).at(trueTargetLoc.second).isTrueTarget = true;
        
        //set attacker location
        atStart = attackerStart;
        
        
    }
    
    //check to see if strategy is valid
    bool validAStrat(vector<pair<int,int> > aStrat);
    
    //print the details of a Node at a given location
    void printNode(pair<int,int> location);
    
    //evaluate attacker strategy
    int evalAStrat(vector<pair<int, int> > aStrat);
    
    //evalDStrat
    int evalDStrat(vector<pair<int,int> > dStrat);
    
    //print all node info
    void printAllNodeInfo();
    
    //simple get functions
    pair<int, int> getTrueTargetLoc();
    vector<pair<int,int> > getTargetLocs();
    int getMoveTax();
    int getGuessTax();
    pair<int,int> getAtStart();
    
    /*set functions*/
    
    //change the true target location
    void setTrueTargetLoc(pair<int,int> loc);
    
    //add a target location
    void setTargetLoc(pair<int,int> loc);
    
    //remove target location
    void removeTargetLoc(pair<int, int> loc);
    
    //set move and guess tax
    void setMoveTax(int a);
    void setGuessTax(int b);
    
    //set attacker's starting location
    void setAtStart(pair<int,int> loc);
};



#endif /* defined(__pGame__board__) */
