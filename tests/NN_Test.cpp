/* 
 * File:   NN_Test.cpp
 * Author: tbecker
 *
 * Created on November 4, 2013, 8:46 PM
 */

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "csv_v3.h"
#include "sb.h"

/*
 * Simple C++ Test Suite
 */

using namespace std;

void test_2d() {
    const size_t d = 2;
    vector<vector<double>> x;
    io::CSVReader<2> in("./tests/test_data.csv");
    double x1; double x2;
    size_t n = 0;
    while(in.read_row(x1, x2)){ x.push_back(vector<double>{x1,x2}); }
    cout<<"NN_Test reading CSV File"<<endl;
    cout<<x.size()<<" lines read"<<endl;
    for(size_t i=0; i<x.size(); i++){
        for(size_t j=0; j<d; j++){
            cout<<x[i][j]<<" ";
        }
        cout<<endl;
    }
    sb s1(x.size(),d,x); //declaration
    cout<<"distance between p0 and p1: "<<s1.dist(0,1)<<endl;
}

void test_4d(size_t n,size_t d) {
    mt19937 r;
    uint32_t seed_val = 1;
    r.seed(seed_val);
    normal_distribution<double> normal_dist(0.0, 1.0);
    
    vector<vector<double>> x(n,vector<double>(d));
    for(size_t i=0;i<n;i++){
        for(size_t j=0;j<d;j++){
            x[i][j] = normal_dist(r);
        }
    }
    for(size_t i=0;i<n;i++){
        for(size_t j=0;j<d;j++){
            cout<<x[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% NN_Test" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (NN_Test)" << std::endl;
    test_2d();
    std::cout << "%TEST_FINISHED% time=0 test_2d (NN_Test)" << std::endl;
    test_4d(4,5);
    std::cout << "%SUITE_FINISHED% time=0" << std::endl;
}