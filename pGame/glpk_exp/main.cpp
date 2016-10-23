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
#include "attacker.h"
using std::pair;
using std::make_pair;
using std::cout;
int main(int argc, const char * argv[]) {
    //create an example board
    vector<pair<int,int> > testTargets;
    testTargets.push_back(make_pair(0,0));
    testTargets.push_back(make_pair(1,1));
    testTargets.push_back(make_pair(2,2));
    
    Board testBoard(3, 3, testTargets, make_pair(0,0), make_pair(2,0),1,3,0);
    //testBoard.printAllNodeInfo();
    
    vector<pair<int,int> > validStrat;
    validStrat.push_back(make_pair(2,0));
    validStrat.push_back(make_pair(2,1));
    validStrat.push_back(make_pair(2,2));
    validStrat.push_back(make_pair(1,2));
    validStrat.push_back(make_pair(1,1));
    validStrat.push_back(make_pair(1,0));
    validStrat.push_back(make_pair(0,0));
    
    vector<pair<int,int> > badStartStrat;
    badStartStrat.push_back(make_pair(0,0));
    badStartStrat.push_back(make_pair(1,1));
    badStartStrat.push_back(make_pair(0,0));
    
    vector<pair<int,int> > badEndStrat;
    badEndStrat.push_back(make_pair(2,0));
    badEndStrat.push_back(make_pair(1,0));
    
    vector<pair<int,int> > badConStrat;
    badConStrat.push_back(make_pair(2,0));
    badConStrat.push_back(make_pair(1,0));
    badConStrat.push_back(make_pair(2,1));
    badConStrat.push_back(make_pair(0,0));
    
    
    cout << "valid strategy is valid?..." <<  testBoard.validAStrat(validStrat) << "\n";
    cout << "bad start strat is valid?..." <<  testBoard.validAStrat(badStartStrat) << "\n";
    cout << "bad end strat is valid?..." <<  testBoard.validAStrat(badEndStrat) << "\n";
    cout << "bad con strat is valid?..." <<  testBoard.validAStrat(badConStrat) << "\n";
    
    
    Attacker attacker1(testBoard);
    cout << "celing for attacker1 is " << attacker1.getCeling() << "\n";
    cout << "valid strat val is " << testBoard.evalAStrat(validStrat);
    
    return 0;
}
