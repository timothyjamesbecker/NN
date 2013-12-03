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
    k = 1;           //start empty, still have to permute to pick first 
    for(size_t i=0; i<n; i++){ indecies.insert(i); }
    this->P = P;     //pass the reference
    first();
    print_status();
}

NN::NN(const NN& orig) {}

NN::~NN() {}

pair<size_t,size_t> NN::dim(){ return pair<size_t,size_t>(n,d); }

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

/*c++11 style Mersene-Twister engine, fancy, etc
 * returns one random index of P
 */
size_t NN::r_gen(size_t m){
    random_device rd;       //will use special RAND instruction on ivy-bridge+
    mt19937_64 r(rd());     //get a 64-bit engine
    auto t0 = chrono::_V2::steady_clock::now();
    r.seed((size_t)t0.time_since_epoch().count());
    uniform_int_distribution<size_t> pos_ran_int(0,m-1);
    return pos_ran_int(r);
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

pair<size_t,double> NN::max_dist(const size_t q, const set<size_t> Q){
    size_t j = 0;
    double max = numeric_limits<double>::min(), curr = 0.0;
    for(auto &i:Q){
        curr = dist(q,i);
        if(curr > max){ max = curr; j = i; }
    }
    return pair<size_t,double>(j,max);    
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

//come back to later if time permits uses a heap
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

pair<size_t,double> NN::min_dist(const size_t q, const set<size_t> Q){
    size_t j = 0;
    double min = numeric_limits<double>::max(), curr = 0.0;
    for(auto &i:Q){
        curr = dist(q,i);
        if(curr < min){ min = curr; j = i; }
    }
    return pair<size_t,double>(j,min);     
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

//come back later if time permits
size_t NN::min_index2(const size_t q, const set<size_t> Q){
    
}

set<size_t> NN::served(const vector<center> C){
    set<size_t> s;
    for(auto &l:indecies){ //each point
        size_t t = min_dist(l,is).first;

    }
    return s;
}

void NN::first(){
    //work on a center structure------------------------------
    center c;                     //new center point
    size_t K = r_gen(n);          //k=1 randomly pick first point
    c.served = indecies;          //first first serves all
    c.pip = max_dist(K,c.served); //furthest point in cluster
    //c.r       = update in next iteration
    //cpj       = none ---no other-------
    //cpj_alpha = none ---clusters yet---
    //friends   = none ------------------
    centers.insert(pair<size_t,center>(K,c));  //into into the list of centers
    //work on a center structure------------------------------
    
    //update other structures<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    is.insert(K);         //save the cluster index as a set
    max_dists.push_back(c.pip);   //toss in the furthest distance
    push_heap(max_dists.begin(),max_dists.end()); //update the max heap
    k++;                  //update iteration counter k
    //update other structures<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
}

//moves algorithm forward by one
void NN::next(){
    //work on a center structure------------------------------
    pop_heap(max_dists.begin(), max_dists.end()); //send max to end
    pair<size_t,double> max = max_dists.back();   //grab it
    max_dists.pop_back();                         //remove it, no duplicates!
    center c;
    size_t K = max.first;
    
    //update k-1
    
    centers.insert(pair<size_t,center>(K,c));
    
    
    
    
    
    
    
    //*************
    //c.pip = max_dist(c.i,c.served); //furthest point in cluster
    //c.r       = update in next iteration
    //cpj       = none ---no other-------
    //cpj_alpha = none ---clusters yet---
    //friends   = none ------------------
    //centers.insert(c);   //push into the list of centers
    //work on a center structure------------------------------ 
    
    //update other structures<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //is.insert(c.i);         //save the cluster index as a set
    max_dists.push_back(c.pip);   //toss in the furthest distance
    push_heap(max_dists.begin(),max_dists.end()); //update the max heap
    k++;                  //update iteration counter k
}

void NN::print_status(){
    //print the status to check it out
    cout<<"\nP has n="<<dim().first<<" rows\n";
    cout<<"each having d="<<dim().second<<" colums\n";
    cout<<"first point is: ";
    //
    cout<<endl;
}

/*basic display functionality*/
void NN::print_data(){
    for(auto &row:P){
        for(auto &i:row){ cout<<i<<" "; }
        cout<<endl;
    }
}

/*basic display functionality*/
void NN::print_point(const size_t p){
    cout<<"p"<<p<<": ";
    for(auto &i:P[p]){ cout<<i<<" "; }
    cout<<endl;
}