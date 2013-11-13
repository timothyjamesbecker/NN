/* 
 * File:   sb.cpp
 * Author: tbecker
 * 
 * Created on November 4, 2013, 8:47 PM
 */

#include <type_traits>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <random>
#include "c11timer.h"
#include "SB.h"

using namespace std;

SB::SB(const size_t n, const size_t d, const vector<vector<double>> m) {
    this->n = n;
    this->d = d;
    this->m = m;
    cout<<"matrix m's dimensions: "<<m.size()<<endl;
}

SB::SB(const SB&){}

SB::~SB() {
}

double SB::dist(size_t p1, size_t p2){
    double sum = 0.0, diff = 0.0;
    for(size_t i=0; i<d; i++){
        diff = m[p1][i] - m[p2][i];
        sum += diff*diff;
    }
    return (double)sqrt(sum);
}

vector<double> SB::all_dist(size_t p){
    vector<double> x;
    for(size_t i=0;i<n;i++){
        if(p != i){ x.push_back(dist(p,i)); }
    }
    return x;
}

vector<double> SB::get_point(size_t p){ return m[p]; }

vector<double>::iterator SB::min_dist(size_t p){
    vector<double> D = all_dist(p);
    return std::min_element(begin(D),end(D));
}

vector<double>::iterator SB::max_dist(size_t p){
    vector<double> D = all_dist(p);
    return std::max_element(begin(D),end(D));
}

int SB::gen(int m){ return rand()%m; }

size_t SB::r_gen(size_t m){
    auto t0 = chrono::_V2::steady_clock::now();
    this->r.seed((size_t)t0.time_since_epoch().count());
    uniform_int_distribution<size_t> pos_ran_int(0,m-1);
    return pos_ran_int(r);
}

vector<size_t> SB::permute_points(){
    auto t0 = chrono::_V2::steady_clock::now();
    unsigned seed = (size_t)t0.time_since_epoch().count();
    
    vector<size_t> p(n),q;
    for(size_t i=0;i<n;i++){ p[i] = i; }
    size_t m = n;
    //for(size_t i=0; i<n; i++){ q.push_back(r_gen(m--)); }
    random_shuffle(p.begin(),p.end());
    return p;
}

size_t SB::size(){ return m.size(); }

void SB::print_matrix(){
    for(auto &row:m){
        for(auto &i:row){ cout<<i<<" "; }
        cout<<endl;
    }
}

void SB::print_point(const size_t p){
    cout<<"value for p"<<p<<": ";
    for(auto &i:m[p]){ cout<<i<<" "; }
    cout<<endl;
}