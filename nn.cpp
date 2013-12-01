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
    this->p_order = permute_points(); //generate a random perm of indexes
    cout<<"\nP has n="<<P.size()<<" rows\n";
    cout<<"each having d="<<P[0].size()<<" colums\n";
}

NN::NN(const NN& orig) {}

NN::~NN() {}

/*c++11 style Mersene-Twister engine, fancy, etc
 * returns one random index of P
 */
size_t NN::r_gen(size_t m){
    auto t0 = chrono::_V2::steady_clock::now();
    this->r.seed((size_t)t0.time_since_epoch().count());
    uniform_int_distribution<size_t> pos_ran_int(0,m-1);
    return pos_ran_int(r);
}

/*Given P: randomly selects a permutation of the indecies
 * and returns these as a vector<size_t>
 */
vector<size_t> NN::permute_points(){
    //auto t0 = chrono::_V2::steady_clock::now();            //put MT back here
    //unsigned seed = (size_t)t0.time_since_epoch().count(); //inside the shuffle
    
    vector<size_t> p(n),q;
    for(size_t i=0;i<n;i++){ p[i] = i; }
    random_shuffle(p.begin(),p.end()); //third argument is a random engine?
    return p;
}