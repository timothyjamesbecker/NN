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
#include "csv_v3.h"
#include "sb.h"

/*
 * Simple C++ Test Suite
 */

using namespace std;

void test_2d() {
    io::CSVReader<2> in("./tests/test_data.csv");
    double x1; double x2;
    while(in.read_row(x1, x2)){
        // do stuff with the data
        cout<<x1<<" "<<x2<<" \n";
    }
    std::cout << "NN_Test reading CSV File" << std::endl;
}

void test_4d(size_t n,size_t d) {
    vector<vector<double>> x(n,vector<double>(d));
    for(int i=0;i<n;i++){
        for(int j=0;j<d;j++){
            x[i][j] = 0.0;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<d;j++){
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