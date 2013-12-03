/* 
 * File:   nn2.h
 * Author: tbecker
 *
 * Created on December 2, 2013, 5:48 PM
 */

#ifndef NN2_H
#define	NN2_H
#include <vector>
#include <set>

using namespace std;

typedef pair<size_t,double> point;
typedef pair<size_t,point>  line;
typedef pair<size_t,vector<point>> cluster;

class NN2 {
public:
    NN2(const vector<vector<double>> M);
    NN2(const NN2& orig);
    virtual ~NN2();
    size_t r_gen(size_t m);
    vector<size_t> permute_indecies();
    pair<size_t,size_t> dim();
    double dist(const size_t p1, const size_t p2);
    map<size_t,point> min_c_dist(const set<size_t> C, const set<size_t> P);
    point max_dist(const size_t q, const set<size_t> Q);
    point min_dist(const size_t q, const set<size_t> Q);
    line max_line(const map<size_t,point> M);
    void next();
    void print_P();
    void print_dim();
    void print_ps();
    void print_cs();
    void print_ps_alphas();
private:
    size_t n,d,k,i;     
    vector<vector<double>> P;      // original data to read from
    set<size_t> ps;                // point indecies, start full
    set<size_t> cs;                //center indecies, start empty
    map<size_t,vector<point>> c_s; 
    map<size_t,point> ps_alphas;   // point index, cluster index, distance
    vector<point> max_dists;       // cache all points calculations
};

#endif	/* NN2_H */

