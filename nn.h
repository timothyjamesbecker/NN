/* 
 * File:   nn.h
 * Author: tbecker
 *
 * Created on November 4, 2013, 8:47 PM
 */

#ifndef NN_H
#define	NN_H
#include <random>
#include <vector>
#include <tuple>
#include <unordered_map>

using namespace std;

typedef struct {
    size_t i;          //index into the set P: P[i]
    size_t pip;        //index into the set P: served by this cluster that is farthest
    double pip_alpha;  //distance d(pi,pip)
    size_t cpj;        //index into the set C: that is the closest
    double cpj_alpha;  //closest cluster center distance not including self
    double r,r4,r8;    //ri, 4*ri, 8*ri precomputed
    unordered_map<size_t,size_t> served;  //list of q in P that have pi as closest center
    unordered_map<size_t,size_t> friends; //list of centers that <= min{8*rk,4*ri}
} cluster;

class NN {
public:
    NN(const vector<vector<double>> P);
    NN(const NN& orig);
    virtual ~NN();
    double dist(size_t p1, size_t p2);
    size_t r_gen(size_t m);
    vector<size_t> permute_points(); 
private:
    size_t n; //number of rows/instances/points in the data set
    size_t d; //number of dimensions for NN/RNN searching
    mt19937_64 r; //needed for random number generation
    vector<size_t> p_order;
    vector<vector<double>> P; //original data to read from
    vector<cluster> centers;  //used for greedy permutation algorithm
    vector<vector<double>> dist_heaps; //one dist max_heap for every point
};
#endif	/* NN_H */

