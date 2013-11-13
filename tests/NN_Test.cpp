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
#include "SB.h"

using namespace std;

void test_2d() {
    const size_t d = 2, p0 = 0, p1 = 1;
    vector<vector<double>> x;
    io::CSVReader<2> in("./tests/test_data.csv");
    double x1; double x2;
    size_t n = 0;
    while(in.read_row(x1, x2)){ x.push_back(vector<double>{x1,x2}); }
    SB sb(x.size(),d,x); //declaration
    cout<<"NN_Test reading CSV File"<<endl;
    cout<<sb.size()<<" lines read"<<endl;
    sb.print_matrix();
    cout<<"value for p"<<p0<<": ";
    sb.print_point(p0);
    cout<<"value for p"<<p1<<": ";
    sb.print_point(p1);
    cout<<"distance between p0 and p1: "<<sb.dist(p0,p1)<<endl;
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