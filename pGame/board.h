/*
 This is the Header File for the Board Structure. The Board is esentially a 2D Vector of Nodes. Each Node
 stores an identifier for being a potential target, a true target, the appropriate probability of being 
 a true target, and a vector of references to other nodes. Currently, the pGame structure is only equipped 
 to deal with rectangular grids.
 */

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
using std::string;
class Board{
private:
    struct Node{
        int rCoord;
        int cCoord;
        vector<Node*> connections;
        bool isTarget;
        bool isTrueTarget;
        double probability;
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
    
    //width and height of the board
    double width;
    double height;
    
    //2D vector storing the nodes
    vector<vector<Node>> nodes;
    
    //list of target locations
    vector<pair<int,int>> targets;
    
    //location of attacker's intended target
    pair<int,int> trueTarget;
    
    //attacker's starting location
    pair<int,int> atStart;
    
    //attacker's penalty for moving
    double moveTax;
    
    //defender's reward for correct prediction
    double guessTax;
    
    //reward for reaching the true target
    double trueTargetReward;
    
    //vector of probabilites for each target being the true target
    vector<double> trueTargetProbs;
public:
    //default constructor
    Board(){}
    Board(int w, int h, vector<pair<int,int>> targetLocs, vector<double> targetProbs, pair<int, int> trueTargetLoc, pair<int, int> attackerStart, double mt, double gt, double ttr){
        trueTargetProbs = targetProbs;
        moveTax = mt;
        guessTax = gt;
        trueTargetReward = ttr;
        //fill 2D Vector with empty Nodes
        vector<Node> row;
        for(int j=0; j<w; ++j){
            Node tempNode;
            row.push_back(tempNode);
        }
        for(int i=0; i<h; ++i){
            nodes.push_back(row);
        }
        //set width and height variables for later
        width = w;
        height = h;
        //establish connections from nodes to all neighbors (only equipped for rectangular)
        for(int i=0; i<height; ++i){
            for(int j=0; j<width; ++j){
                nodes.at(i).at(j).rCoord = i;
                nodes.at(i).at(j).cCoord = j;
                if(i>0){nodes.at(i).at(j).connections.push_back(&nodes.at(i-1).at(j));}
                if(j>0){nodes.at(i).at(j).connections.push_back(&nodes.at(i).at(j-1));}
                if(i<height-1){nodes.at(i).at(j).connections.push_back(&nodes.at(i+1).at(j));}
                if(j<width-1){nodes.at(i).at(j).connections.push_back(&nodes.at(i).at(j+1));}
            }
        }
        
        //set target identifiers to false
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
            nodes.at((targetLocs.at(x)).first).at((targetLocs.at(x)).second).probability = targetProbs.at(x);
        }
        
        //mark the true target's true target identifier
        trueTarget = trueTargetLoc;
        nodes.at(trueTargetLoc.first).at(trueTargetLoc.second).isTrueTarget = true;
        
        //set attacker location
        atStart = attackerStart;
    }
    
    
//STRATEGY EVALUATION-----------------------------------------------------------------------
    //check to see if strategy is valid
    bool validAStrat(vector<pair<int,int>> aStrat);
    //evaluate attacker strategy
    double evalAStrat(vector<pair<int, int>> aStrat);
    //evalDStrat
    double evalDStrat(vector<pair<int,int>> dStrat);
    
//PRINTING NODE INFORMATION-----------------------------------------------------------------
    //print the details of a Node at a given location
    void printNode(pair<int,int> location);
    //print all node info
    void printAllNodeInfo();
    
//GET FUNCTIONS-----------------------------------------------------------------------------
    pair<int, int> getTrueTargetLoc();
    vector<pair<int,int>> getTargetLocs();
    vector<pair<int,int>> getTargets();
    double getTargetProb(pair<int, int> p );
    double getMoveTax();
    double getGuessTax();
    pair<int,int> getAtStart();
    double getTrueTargetReward();
    int getWidth();
    int getHeight();
    
//SET FUNCTIONS------------------------------------------------------------------------------
    //change the true target location
    void setTrueTargetLoc(pair<int,int> loc);
    //add a target location
    void setTargetLoc(pair<int,int> loc);
    //remove target location
    void removeTargetLoc(pair<int, int> loc);
    //set move and guess tax
    void setMoveTax(double a);
    void setGuessTax(double b);
    //set attacker's starting location
    void setAtStart(pair<int,int> loc);
    
//HELPER FUNCTIONS----------------------------------------------------------------------------
    //reward function
    double reward(pair<int, int> attackerLocation, pair<int, int> defenderPrediction, pair<int, int> attackerAction, pair<int, int> assumedTheta);
    //return list of connections (equipped only for rectangular board)
    vector<pair<int,int>> getConnectionsOfNode(pair<int,int> loc);
    //quick function that returns true if the node at the given location is a potential target
    bool isNodeATarget(pair<int, int> loc);
    //creates a variable string for the .lp file. [Example]: "V((0,0),(1,1))
    string createVariableForLp(string pre, pair<int, int> assumedTarget, pair<int, int> state);
};



#endif /* defined(__pGame__board__) */
