/* 
 * File:   NN_Test.cpp
 * Author: tbecker
 *
 * Created on November 4, 2013, 8:46 PM
 */

#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <tuple>
#include <map>
#include <unordered_map>
#include <set>
#include "csv_v3.hpp"
#include "nn.h"
#include "nn2.h"
#include "sb.h"
#include "c11timer.h"

using namespace std;

void test_2d() {
    const size_t n = 100, d= 2,p0 = 3, p1 = 2;
    vector<vector<double>> x;
    io::CSVReader<d> in("./tests/test_data.csv");
    double x1; double x2;
    while(in.read_row(x1, x2)){ x.push_back(vector<double>{x1,x2}); }
    SB sb(x.size(),d,x); //declaration
    cout<<"NN_Test reading CSV File"<<endl;
    cout<<sb.size()<<" lines read"<<endl;
    //cout<<"distance between p0 and p1: "<<sb.dist(p0,p1)<<endl; //distance
    //auto D = sb.all_dist(p0);                                   //distance
    //cout<<"all distances from p0 to P\\p0:"<<endl;              //alldist
    //for(auto &i: D){ cout<<i<<endl; }                           //alldist
    //vector<size_t> P = sb.permute_points();                     //permute
    //for(auto &i:P){ sb.print_point(i); }                        //permute
    auto D = sb.get_dist_heaps();                                    //all max-heaps
    for(size_t i=0; i<n; i++){
        cout<<"SB data structure: max-heap for p="<<(i+1)<<":";
        for(size_t j=0; j<n-1; j++){
                (j%10==0)? cout<<endl<<D[i][j]<<" " : cout<<D[i][j]<<" ";
        }
        cout<<endl<<endl;
    }
    //sb.print_dist_heaps();
}

void test_nn(size_t n, size_t d){
    mt19937_64 r;
    random_device rd;
    r.seed(rd());
    normal_distribution<double> normal_dist(0.0, 1.0);
    vector<vector<double>> x(n,vector<double>(d));
    for(size_t i=0;i<n;i++){
        for(size_t j=0;j<d;j++){
            x[i][j] = normal_dist(r);
        }
    }
    NN nn(x);
    size_t q = 0;
    set<size_t> Q = {1,2,3};
    
    nn.print_data();
    cout<<endl;
    cout<<nn.dist(q,1)<<endl;
    cout<<nn.dist(q,2)<<endl;
    cout<<nn.dist(q,3)<<endl;
    cout<<endl<<"max distance index"<<endl;
    cout<<nn.max_index(q,Q)<<endl;
    
    size_t* i;
    size_t j = 123;
    
    i = &j;
    cout<<*i<<endl;
}

void test_nn2(size_t n, size_t d){
    mt19937_64 r;
    random_device rd;
    r.seed(rd());
    normal_distribution<double> normal_dist(0.0, 1.0);
    vector<vector<double>> x(n,vector<double>(d));
    for(size_t i=0;i<n;i++){
        for(size_t j=0;j<d;j++){
            x[i][j] = normal_dist(r);
        }
    }
    NN2 nn(x);  //instantiate
    
    //test out the max_map
    map<size_t,point> P;      //map with key as distance
    for(size_t i=0; i<n; i++){
        pair<size_t,double> p0(0,x[i][1]);  //static cluster reference
        P.insert(line(i,p0));
    } //retrieve index of max key
    auto m = nn.max_line(P);
    cout<<"P key, value pairs: "<<"\n\n";
    for(auto &i:P){ cout<<i.first<<" "<<i.second.first<<" "<<i.second.second<<endl; }
    cout<<endl<<"max found was: "<<m.first<<" "<<m.second.second<<endl;
    nn.next();
}


void test_um(){
    vector<vector<double>> P = {{1.0,0.0},{0.0,2.0},{3.0,4.0}};
    set<size_t> served;
    set<size_t> friends;
    unordered_map<pkey,double> dist_heap;
    pkey K;
    
    for(size_t i = 0; i < P.size(); ++i){
        for(size_t j = 0; j < P[i].size(); ++j){
            K.first = i;
            K.second = j;
            dist_heap[K] = 8.0;
        }
    }
    
    for(size_t i = 0; i < P.size(); ++i){
        for(size_t j = 0; j < P[i].size(); ++j){
            K.first = 2;
            K.second = 1;
            if(dist_heap.find(K)==dist_heap.end()){cout<<"Not found...";}
        }
    }
    
    cout<<"dist heap contains: ";
    for(auto &i:dist_heap){ cout<<i.second<<" "; }
    /*for(auto i=served.begin(); i != served.end(); ++i){
        cout<<i->first<<" "<<i->second<<" "; this is for an unordered map
    }*/
    cout<<endl;
    
    served.insert(2);
    served.insert(3);
    served.insert(4);
    
    cout << "served contains:";
    /*for(auto i=served.begin(); i != served.end(); ++i){
        cout<<i->first<<" "<<i->second<<" "; this is for an unordered map
    }*/
    for(auto &i:served){ cout<<i<<" "; }
    cout<<endl;
    
}

void test_set(){
    /*mt19937_64 r;
    r.seed(1);
    normal_distribution<double> normal(0.0, 1.0);
    vector<double> P;
    for(size_t i=0; i<100; i++){ P.push_back(normal(r)); } //make 100 points
    set<size_t> A,B,C,D;
    for(auto &i:P){ cout<<i<<" "; }
    
    for(size_t i=0; i<P.size(); i++){
        if(i<25){ A.insert(i); }
        if(i>24&&i<50){ B.insert(i); }
        if(i>49&&i<75){ C.insert(i); }
        if(i>74){ D.insert(i); }
    }
    cout<<endl<<*B.find(2)<<endl;
    for(auto &i:A){ cout<<P[i]<<" "; }
    */
    set<size_t> A = {0,1,2,3};
    A.insert(4); A.insert(1);
    set<size_t> B = {0,0,2};
    set<size_t> C;
    //set_difference(A.begin(),A.end(),
    //               B.begin(),B.end(),inserter(C,C.begin()));
    set_union(A.begin(),A.end(),
              B.begin(),B.end(),inserter(C,C.begin()));
    for(auto &i:C){ cout<<i<<" "; }
    
}

int main(int argc, char** argv) {
    C11Timer t;
    cout<<endl;
    cout << "%SUITE_STARTING% NN_Test" << endl;
    cout << "%SUITE_STARTED%" << endl<<endl;
    cout << "%TEST_STARTED% test1 (NN_Test)" << endl;
    t.ping();
    //test_nn(4,5);
    //test_um();
    //test_set();
    test_nn2(20,5);
    t.ping();
    cout<<endl;
    cout << "%TEST_FINISHED% time="<<t.ms()<<"ms test_2d (NN_Test)" << endl;
    cout << "%SUITE_FINISHED% time=0" << endl;
}