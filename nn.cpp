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
#include <limits>
#include "nn.h"

NN::NN(const vector<vector<double>> P) {
    n = P.size();    //number of points in the set
    d = P[0].size(); //need the same dim
    this->P = P;           //pass the reference
    for(size_t i=0; i<n; i++){ indecies[i] = i; }
    perm_seq = permute_indecies(); //generate a random perm of indexes
    
    //print the output to check it out
    cout<<"\nP has n="<<dim()[0]<<" rows\n";
    cout<<"each having d="<<dim()[1]<<" colums\n";
    cout<<"permutation order is: ";
    for(auto &i: perm_seq){ cout<<i<<" "; }
    cout<<endl;
}

NN::NN(const NN& orig) {}

NN::~NN() {}

vector<size_t> NN::dim(){
    vector<size_t> t = {n, d};
    return t;
}

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

/*Euclidian Distance Function, will make more of these, etc
 * p1 - the first data element
 * p2 - the second data element
 * returns the euclidian distance from p1 to p2
 */
double NN::dist(const size_t p1, const size_t p2){
    double sum = 0.0, diff = 0.0;
    for(size_t i=0; i<d; i++){
        diff = P[p1][i] - P[p2][i];
        sum += diff*diff;
    }
    return (double)sqrt(sum);
}

//returns the max dist index into P of q to set Q=subset(P)
//this version recomputes all distances from q to subset Q
size_t NN::max_index(const size_t q, const set<size_t> Q){
    size_t j = 0;
    double max = numeric_limits<double>::min(), curr = 0.0;
    for(auto &i:Q){
        curr = dist(q,i);
        if(curr > max){ max = curr; j = i; }
    }
    return j;
}

//come back to later if have time
size_t NN::max_index2(const size_t q, const set<size_t> Q){
    size_t j = 0;
    double max = numeric_limits<double>::min();
    for(auto &i:Q){
        pkey K(i,q);
        auto curr = comp_dists.find(K);
        if(curr==comp_dists.end()){ curr->second = dist(q,i); } //if not in heap
        if(curr->second > max){ max = curr->second; j = i; }     //otherwise it was fetched
    }
    return j;
}

//returns the min dist index into P of q to set Q=subset(P)
size_t NN::min_index(const size_t q, const set<size_t> Q){
    size_t j = 0;
    double min = numeric_limits<double>::max(), curr = 0.0;
    for(auto &i:Q){
        curr = dist(q,i);
        if(curr < min){ min = curr; j = i; }
    }
    return j;    
}
size_t NN::min_index2(const size_t q, const set<size_t> Q){
    
}

/*basic display functionality*/
void NN::print_data(){
    for(auto &row:P){
        for(auto &i:row){ cout<<i<<" "; }
        cout<<endl;
    }
}

void NN::print_dist_heaps(){
    for(auto &i:dist_heaps[0]){ cout<<i<<" "; }
    cout<<endl;
}

/*basic display functionality*/
void NN::print_point(const size_t p){
    cout<<"p"<<p<<": ";
    for(auto &i:P[p]){ cout<<i<<" "; }
    cout<<endl;
}