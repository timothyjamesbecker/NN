/* 
 * File:   nn2.cpp
 * Author: tbecker
 * 
 * Created on December 2, 2013, 5:48 PM
 */
#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>
#include <vector>
#include <chrono>
#include <limits>
#include "nn2.h"

NN2::NN2(const vector<vector<double>> M, size_t K) {
    P = M; //reference to data matrix
    this->K = K; //the number of clusters to make
    n = M.size();    //number of points in the set
    d = M[0].size(); //need the same dim
    k = 1;           //start empty, still have to permute to pick first 
    for(size_t i=0; i<n; i++){ ps.insert(i); }  //p_s starts with all P
    //--------------------------------------------------c_s starts empty
    
    //setup for first center: k=1 <<<<<<<<<<<<
    auto r = r_gen(n); //randomly pick p1
    cs.insert(r);      //add pi to centers
    ps_alphas = min_c_dist(cs, ps);
    //ps.erase(r);       //remove pi from points
    k++;
    //setup for initial<<<<<<<<<<<<<<<<<<<<<<<
}

NN2::NN2(const NN2& orig) {}

NN2::~NN2() {}

/*c++11 style Mersene-Twister engine, fancy, etc
 * returns one random index of P
 */
size_t NN2::r_gen(size_t m){
    random_device rd;       //will use special RAND instruction on ivy-bridge+
    mt19937_64 r(rd());     //get a 64-bit engine
    uniform_int_distribution<size_t> pos_ran_int(0,m-1);
    return pos_ran_int(r);
}

/*Given P: randomly selects a permutation of the indecies
 * and returns these as a vector<size_t>
 * c++11 style Mersene-Twister engine used
 */
vector<size_t> NN2::permute_indecies(){
    random_device rd;       //will use special RAND instruction on ivy-bridge+
    mt19937_64 r(rd());     //get a 64-bit engine
    vector<size_t> p(n),q;  //the permutation values
    for(size_t i=0;i<n;i++){ p[i] = i; } //populate integers
    shuffle(p.begin(),p.end(),r); //apply the rand engine here
    return p;                     //pretty nice perm here
}

pair<size_t,size_t> NN2::dim(){ return pair<size_t,size_t>(n,d); }

/*Euclidian Distance Function, will make more of these, etc
 * p1 - the first data element
 * p2 - the second data element
 * returns the euclidian distance from p1 to p2
 */
double NN2::dist(const size_t p1, const size_t p2){
    double sum = 0.0, diff = 0.0;
    for(size_t i=0; i<d; i++){
        diff = P[p1][i] - P[p2][i];
        sum += diff*diff;
    }
    return (double)sqrt(sum);
}

/* computes the closest cluster for every point
 * saves as point, cluster, distance to a map with point as the key
 */
map<size_t,point> NN2::min_c_dist(const set<size_t> C, const set<size_t> P){
    map<size_t,point> D;
    for(auto &p: P){
        point min(p,numeric_limits<double>::max()); //set next point
        for(auto &c: C){
            double t = dist(p,c);
            if(t<min.second){ min.first = c; min.second = t; }
        }
        D.insert(line(p,min)); //insert key p pointing to min cluster
    }
    return D;
}

point NN2::max_dist(const size_t q, const set<size_t> Q){
    size_t j = 0;
    double max = numeric_limits<double>::min(), curr = 0.0;
    for(auto &i:Q){
        curr = dist(q,i);
        if(curr > max){ max = curr; j = i; }
    }
    return point(j,max);    
}

point NN2::min_dist(const size_t q, const set<size_t> Q){
    size_t j = 0;
    double min = numeric_limits<double>::max(), curr = 0.0;
    for(auto &i:Q){
        curr = dist(q,i);
        if(curr > min){ min = curr; j = i; }
    }
    return point(j,min);    
}

line NN2::max_line(const map<size_t,point> M){
    return *max_element(M.begin(),M.end(),
                [](const line& p1, const line& p2){
                    return p1.second.second < p2.second.second; });      
}

void NN2::next(){ //now you keep calling  next() k times...
    while(k <= K){//general center: k>1 <<<<<<<<<<<<<<<<<<<<<<<<<<<
        //setup for general center: k>1 <<<<<<<<<<<<<<<<<<<<<<<<<<<
        auto r = max_line(ps_alphas);        // get max alpha index
        cs.insert(r.first);                  //add pi to centers
        ps_alphas = min_c_dist(cs, ps);      //update the clusters
        //ps.erase(r.first);                   //remove pi from points
        k++;
    }
    //setup for general<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 
}

void NN2::print_P(){
    cout<<"all points: "<<endl;
    for(auto &row:P){
        for(auto &i:row){ cout<<i<<" "; }
        cout<<endl;
    }
    cout<<endl;
}

void NN2::print_dim(){
   cout<<"n="<<dim().first<<endl;;
   cout<<"d="<<dim().second<<endl;
}

void NN2::print_ps(){
    //cout<<"ps: ";
    for(auto &i:ps){ cout<<i<<" "; }
    cout<<endl;
}

void NN2::print_cs(){
    //cout<<"cs: ";
    for(auto &i:cs){ cout<<i<<" "; }
    cout<<endl;    
}

void NN2::print_ps_alphas(){
    //index of point, index of cluster, distance
    for(auto &i:ps_alphas){
        cout<<i.first<<" "<<i.second.first<<" "<<i.second.second<<endl;
    }
    
}