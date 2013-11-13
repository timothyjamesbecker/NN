/* 
 * File:   SB.cpp
 * Author: tbecker
 * 
 * Created on November 4, 2013, 8:47 PM
 */

#include "SB.h"
#include <type_traits>
#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

using namespace std;

sb::sb(const size_t n, const size_t d, const vector<vector<double>> m) {
    this->n = n;
    this->d = d;
    this->m = m;
    cout<<"matrix m's dimensions: "<<m.size()<<endl;
}

sb::sb(const sb&){}

sb::~sb() {
}

double sb::dist(size_t p1, size_t p2){
    double sum = 0.0, diff = 0.0;
    for(size_t i; i<d; i++){
        diff = m[p1][i] - m[p2][i];
        sum += diff*diff;
    }
    return (double)sqrt(sum);
}

vector<double> sb::get_point(size_t p1){ return m[p1]; }

vector<double> sb::minimum(vector<vector<double>> s){
    vector<double> x = {1.0,2.0,3.0};
    return x;
}

size_t sb::size(){ return m.size(); }

void sb::print_point(size_t p1){
    for(auto &i:m[p1]){ cout<<i; }
}