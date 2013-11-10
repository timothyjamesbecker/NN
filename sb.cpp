/* 
 * File:   NN.cpp
 * Author: tbecker
 * 
 * Created on November 4, 2013, 8:47 PM
 */

#include "sb.h"
#include <type_traits>
#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

using namespace std;

sb::sb(size_t n, size_t d, vector<vector<double>> m) {
    this->n = n;
    this->d = d;
    //static_assert(m.size()>0,"No dimension...");
    cout<<"matrix m's dimensions: "<<m.size()<<endl;
    this->m = m;
}

sb::sb(const sb&){}

sb::~sb() {
}

double sb::dist(size_t p1, size_t p2){
    double sum = 0.0, diff;
    for(size_t i; i<d; i++){     
        diff = m[p1][i] - m[p2][i];
        sum += diff*diff;
    }
    return (double)sqrt(sum);
}

vector<double> sb::minimum(vector<vector<double>> s){
    vector<double> x = {1.0,2.0,3.0};
    return x;
}