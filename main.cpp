/* 
 * File:   main.cpp
 * Author: tbecker
 *
 * Created on November 4, 2013, 8:54 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include "nn2.h"

using namespace std;

/*
 * main nn command line program with arguments
 */
int main(int argc, char** argv) {
    string csv_in_file(argv[0]); //argv[0] is the file name, 1+ is args
    int k = atoi(argv[1]); //number of clusters to sample 
    //cout<<"number of clusters: "<<k<<endl;;
    int d = atoi(argv[2]); //number of dim in stream
    //cout<<"number of dimensions: "<<d<<endl;
    int n = atoi(argv[3]); //number of points in stream
    //cout<<"number of points: "<<n<<endl;
    
    vector<double> y;
    vector<vector<double>> x(n,vector<double>(d));
    for(auto i=4; i< argc; i++){ y.push_back(atof(argv[i])); }
    
    int m = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<d; j++){ x[i][j] = y[m++]; }
    }
    NN2 nn(x,k);   //start it up
    nn.next();     //get clusters
    nn.print_cs(); //print out the permutation in order
    
    return 0;
}

