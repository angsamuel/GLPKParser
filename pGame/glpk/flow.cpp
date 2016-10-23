//
//  main.cpp
//  flow
//
//  Created by Samuel Ang on 4/2/16.
//  Copyright (c) 2016 Samuel Ang. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <queue>
#include <tuple>
using std::queue;
using std::vector;
using std::tuple;
using std::get;
using std::make_tuple;
using std::cout;

tuple<int, vector<int>> bst(vector<vector<int>> &capacityMatrix, vector<vector<int>> &neighborLists, int start, int end, vector<vector<int>> &F){
    vector<int> P(capacityMatrix.size(), -1);
    P.at(start) = -2;
    vector<int> M(capacityMatrix.size(), 0);
    M.at(start) = INT_MAX;
    queue<int> Q;
    Q.push(start);
    while(Q.size()>0){
        int u = Q.front();
        Q.pop();
        for(int v : neighborLists.at(u)){
            if(capacityMatrix.at(u).at(v) - F.at(u).at(v) > 0 && P.at(v) == -1){
                P.at(v) = u;
                M.at(v) = std::min(M.at(u),capacityMatrix.at(u).at(v) - F.at(u).at(v));
                if(v != end){
                    Q.push(v);
                }else{
                    return make_tuple(M.at(end),P);
                }
            }
        }
    }
    return make_tuple(M.at(end), P);
}

vector<tuple<int,int,int>> courierLoads(const vector<int> &orders, const vector<tuple<int,int,int>> &capacities){
    
    //capacity matrix
    vector<vector<int>> capacityMatrix;
    vector<int> neg1;
    for(int i = 0; i<orders.size()+1; ++i){
        neg1.push_back(-1);
    }
    for(int i = 0; i<orders.size()+1; ++i){
        capacityMatrix.push_back(neg1);
    }
    
    for(auto x : capacities){
        capacityMatrix.at(get<0>(x)).at(get<1>(x)) = get<2>(x);
    }
    //universal node connections
    for(int i = 0; i<orders.size(); ++i){
        capacityMatrix.at(i).at(orders.size()) = orders.at(i);
    }
    
    //neighbors Matrix
    vector<vector<int>> neighborLists;
    neighborLists.resize(orders.size()+1); //+1 for universal sink
    for(auto x : capacities){
        neighborLists.at(get<0>(x)).push_back(get<1>(x));
    }
    for(int i = 0; i<orders.size(); ++i){
        neighborLists.at(i).push_back(orders.size());
    }
    
    int maxFlow = 0;
    vector<vector<int>> F(orders.size()+1, vector<int>(orders.size()+1,0));
    
    //forever
    while(true){
        auto mP = bst(capacityMatrix, neighborLists, 0, orders.size(), F);
        int m = get<0>(mP);
        vector<int> P = get<1>(mP);
        if(m==0){
            break;
        }
        maxFlow += m;
        int v = orders.size();
        
        while(v!=0){
            int u = P.at(v);
            F.at(u).at(v) += m;
            F.at(v).at(u) -= m;
            v = u;
        }
    }
    int neededFlow = 0;
    for(int x : orders){
        neededFlow += x;
    }
    //cout << "neededFlow: " << neededFlow << "\n";
    if(maxFlow<neededFlow){
        vector<tuple<int,int,int>> emptyVec;
        return emptyVec;
    }
    vector<tuple<int,int,int>> returnVec = capacities;
    
    
    for(int i = 0; i<returnVec.size(); ++i){
        get<2>(returnVec.at(i)) = F.at(get<0>(returnVec.at(i))).at(get<1>(returnVec.at(i)));
    }
    return returnVec;
}
/*
int main(int argc, const char * argv[]) {
    
    //test 1
    cout << "test1\n";
    vector<tuple<int, int, int>> connections;
    vector<int> orders = {0,5};
    connections.push_back(make_tuple(0,1,5));
    auto test1 = courierLoads(orders,connections);
    for(auto m : test1){
        cout << get<0>(m) << " " << get<1>(m) << " " << get<2>(m) << "\n";
    }
    
    //test 2
    cout << "test2\n";
    vector<tuple<int,int,int>> connections2;
    vector<int> orders2 = {0,1,2,3,1};
    connections2.push_back(make_tuple(0,1,5));
    connections2.push_back(make_tuple(0,2,4));
    connections2.push_back(make_tuple(0,3,5));
    connections2.push_back(make_tuple(3,4,10));
    
    auto test2 = courierLoads(orders2,connections2);
    for(auto m : test2){
        cout << get<0>(m) << " " << get<1>(m) << " " << get<2>(m) << "\n";
    }
    
    std::cout << "Hello, World!\n";
    return 0;
}*/
