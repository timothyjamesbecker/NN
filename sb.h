/* 
 * File:   SB.h
 * Author: tbecker
 *
 * Created on November 4, 2013, 8:47 PM
 */
#ifndef sb_H
#define	sb_H
#include <vector>
#include <random>

using namespace std;

class SB {
public:
    SB(const size_t n, const size_t d, const vector<vector<double>> m); //constructor
    SB(const SB&); //copy constructor
    virtual ~SB(); //destructor
    double dist(size_t p1, size_t p2);
    vector<double> all_dist(size_t p);
    vector<vector<double>> all_points_all_dist();
    vector<double> get_point(size_t p);
    vector<double>::iterator min_dist(size_t p);
    vector<double>::iterator max_dist(size_t p);
    int gen(int m);
    size_t r_gen(size_t m);
    vector<size_t> permute_points();
    void make_max_heap(size_t i);
    size_t size();
    void print_matrix();
    void print_point(const size_t p);
private:
    size_t n; //number of rows/instances/points in the data set
    size_t d; //number of dimensions for NN/RNN searching
    mt19937_64 r; //needed for random number generation
    vector<vector<double>> data; //orginal data to read from
    vector<vector<double>> dist_heaps; //one dist max_heap for every point
};

#endif	/* sb_H */

