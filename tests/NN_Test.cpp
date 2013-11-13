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
#include "csv_v3.hpp"
#include "sb.h"
#include "c11timer.h"

using namespace std;

void test_2d() {
    const size_t d = 2, p0 = 3, p1 = 2;
    vector<vector<double>> x;
    io::CSVReader<2> in("./tests/test_data.csv");
    double x1; double x2;
    size_t n = 0;
    while(in.read_row(x1, x2)){ x.push_back(vector<double>{x1,x2}); }
    SB sb(x.size(),d,x); //declaration
    cout<<"NN_Test reading CSV File"<<endl;
    cout<<sb.size()<<" lines read"<<endl;
    cout<<"distance between p0 and p1: "<<sb.dist(p0,p1)<<endl;
    auto D = sb.all_dist(p0);
    cout<<"all distances from p0 to P\\p0:"<<endl;
    for(auto &i: D){ cout<<i<<endl; }
}

void test_4d(size_t n,size_t d) {
    mt19937_64 r;
    r.seed(1);
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
    C11Timer t;
    cout<<endl;
    cout << "%SUITE_STARTING% NN_Test" << endl;
    cout << "%SUITE_STARTED%" << endl<<endl;
    cout << "%TEST_STARTED% test1 (NN_Test)" << endl;
    t.ping();
    test_2d();
    t.ping();
    cout<<endl;
    cout << "%TEST_FINISHED% time="<<t.ms()<<"ms test_2d (NN_Test)" << endl;
    test_4d(4,5);
    cout << "%SUITE_FINISHED% time=0" << endl;
}