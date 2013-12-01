/* 
 * File:   NN.cpp
 * Author: tbecker
 * 
 * Created on November 4, 2013, 8:47 PM
 */
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <chrono>
#include "nn.h"

NN::NN(const vector<vector<double>> P) {
    this->n = P.size();    //number of points in the set
    this->d = P[0].size(); //need the same dim
    this->P = P;           //pass the reference
    this->perm_seq = permute_indecies(); //generate a random perm of indexes 
    cout<<"\nP has n="<<P.size()<<" rows\n";
    cout<<"each having d="<<P[0].size()<<" colums\n";
    cout<<"permutation order is: ";
    for(auto &i: perm_seq){ cout<<i<<" "; }
    cout<<endl;
}

NN::NN(const NN& orig) {}

NN::~NN() {}

/*Given P: randomly selects a permutation of the indecies
 * and returns these as a vector<size_t>
 * c++11 style Mersene-Twister engine used
 */
vector<size_t> NN::permute_indecies(){
    random_device rd;       //will use special RAND instruction on ivy-bridge+
    mt19937_64 r(rd());     //get a 64-bit engine
    vector<size_t> p(n),q;  //the permutation values
    for(size_t i=0;i<n;i++){ p[i] = i; } //populate integers
    shuffle(p.begin(),p.end(),r); //apply the rand engine here
    return p;                     //pretty nice perm here
}