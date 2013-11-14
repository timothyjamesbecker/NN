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

/*SB constructor
 * n - # of data rows/instances/points
 * d - # of dimensions (Clarkson uses 33 and was computing with 32-bit floats
 * data - the data input matrix (using vector of vector of doubles for now
 */
SB::SB(const size_t n, const size_t d, const vector<vector<double>> data) {
    this->n = n;
    this->d = d;
    this->data = data;
    this->dist_heaps = all_points_all_dist();
    for(size_t i=0; i<n; i++){ make_max_heap(i); }
    cout<<"matrix m's dimensions: "<<data.size()<<endl;
}

SB::SB(const SB&){}

SB::~SB() {}

/*Euclidian Distance Function, will make more of these, etc
 * p1 - the first data element
 * p2 - the second data element
 * returns the euclidian distance from p1 to p2
 */
double SB::dist(size_t p1, size_t p2){
    double sum = 0.0, diff = 0.0;
    for(size_t i=0; i<d; i++){
        diff = data[p1][i] - data[p2][i];
        sum += diff*diff;
    }
    return (double)sqrt(sum);
}

/*Given p: computes all distances in P\p
 * will change this to pass a dist function as a param
 */
vector<double> SB::all_dist(size_t p){
    vector<double> q;
    for(size_t i=0;i<n;i++){
        if(p != i){ q.push_back(dist(p,i)); }
    }
    return q;
}
/*Computes for every point pi, the distance to
 * every other point: P\pi returning the result
 */
vector<vector<double>> SB::all_points_all_dist(){
    vector<vector<double>> Q;
    for(size_t i=0; i<n; i++){ Q.push_back(all_dist(i)); }
    return Q;
}

/*Gives the point of some index*/
vector<double> SB::get_point(size_t p){ return data[p]; }

/*Computes and returns to closest element in P\p to p*/
vector<double>::iterator SB::min_dist(size_t p){
    vector<double> D = all_dist(p);
    return std::min_element(begin(D),end(D));
}

/*Computes and returns to furthest element in P\p to p*/
vector<double>::iterator SB::max_dist(size_t p){
    vector<double> D = all_dist(p);
    return std::max_element(begin(D),end(D));
}

/*old-school c random generator*/
int SB::gen(int m){ return rand()%m; }

/*c++11 style Mersene-Twister engine, fancy, etc
 * returns one random index of P
 */
size_t SB::r_gen(size_t m){
    auto t0 = chrono::_V2::steady_clock::now();
    this->r.seed((size_t)t0.time_since_epoch().count());
    uniform_int_distribution<size_t> pos_ran_int(0,m-1);
    return pos_ran_int(r);
}

/*Given P: randomly selects a permutation of the indecies
 * and returns these as a vector<size_t>
 */
vector<size_t> SB::permute_points(){
    //auto t0 = chrono::_V2::steady_clock::now();            //put MT back here
    //unsigned seed = (size_t)t0.time_since_epoch().count(); //inside the shuffle
    
    vector<size_t> p(n),q;
    for(size_t i=0;i<n;i++){ p[i] = i; }
    size_t m = n;
    random_shuffle(p.begin(),p.end()); //third argument is a random engine?
    return p;
}

/* Given an index i, reforms the max_heap for P[i]
 * This is needed when new elements are added
 * and the data inside this vector can grow stale
 */
void SB::make_max_heap(size_t i){
    make_heap(dist_heaps[i].begin(),dist_heaps[i].end());
}

vector<vector<double>> SB::get_dist_heaps(){
    vector<vector<double>> Q = SB::all_points_all_dist();
    for(size_t i=0; i<n; i++){
        make_heap(Q[i].begin(),Q[i].end());
    }
    return Q;
}

/*simple total data size*/
size_t SB::size(){ return data.size(); }

/*basic display functionality*/
void SB::print_data(){
    for(auto &row:data){
        for(auto &i:row){ cout<<i<<" "; }
        cout<<endl;
    }
}

void SB::print_dist_heaps(){
    for(auto &i:dist_heaps[0]){ cout<<i<<" "; }
    cout<<endl;
}

/*basic display functionality*/
void SB::print_point(const size_t p){
    cout<<"p"<<p<<": ";
    for(auto &i:data[p]){ cout<<i<<" "; }
    cout<<endl;
}