/* 
 * File:   NN.cpp
 * Author: tbecker
 * 
 * Created on November 4, 2013, 8:47 PM
 */

#include "sb.h"

sb::sb() {
}

sb::sb(const sb& orig) {
}

sb::~sb() {
}

double sb::dist(matrix<double,1,4> i, matrix<double,1,4> j){
    return 1.0;
}

matrix<double,1,4> sb::minimum(matrix<double,2,4>){
    matrix<double,1,4> x = {{1.0,2.0,3.0}};
    return x;
}