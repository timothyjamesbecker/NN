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
#include <map>
#include <set>

using namespace std;

typedef struct {
    pair<size_t,double> pip; //index into the set P: served by this cluster that is farthest
    pair<size_t,double> cpj; //index into the set P: that is the closest center
    double r,r4,r8;      //ri, 4*ri, 8*ri precomputed
    set<size_t> served;  //list of q in P that have pi as closest center
    set<size_t> friends; //list of centers that <= min{8*rk,4*ri}
} center;

//using a pair of indecies as the key for map, heap, etc
struct pkey {
    size_t first;
    size_t second;
    bool operator==(const pkey &other) const{
        return (first == other.first  && second == other.second ||
                first == other.second && second == other.first);
    }
    pkey(){}
    pkey(size_t p, size_t q){ first = p; second = q; }
};
//define the hash function for a pair key
namespace std {
    template <>
    struct hash<pkey>{
        size_t operator()(const pkey& k) const{
            using std::size_t;
            using std::hash;
            return ((hash<size_t>()(k.first)^(hash<size_t>()(k.second) << 1)) >> 1);
        }
    };
}

class NN {
public:
    NN(const vector<vector<double>> P);
    NN(const NN& orig);
    virtual ~NN();
    pair<size_t,size_t> dim();
    double dist(const size_t p1, const size_t p2);
    size_t r_gen(size_t m);
    vector<size_t> permute_indecies();
    pair<size_t,double> max_dist(const size_t q, const set<size_t> Q);
    //returns the max dist index into P of q to set Q=subset(P)
    size_t max_index(const size_t q, const set<size_t> Q);
        //returns the max dist index into P of q to set Q=subset(P)
    size_t max_index2(const size_t q, const set<size_t> Q);
    //returns the min dist index into P of q to set Q=subset(P)
    pair<size_t,double> min_dist(const size_t q, const set<size_t> Q);
    size_t min_index(const size_t q, const set<size_t> Q);
    //returns the min dist index into P of q to set Q=subset(P)
    size_t min_index2(const size_t q, const set<size_t> Q);
    set<size_t> served(const vector<center> C);
    void first(); //sets the first step
    void next();  //moves algorithm forward k++
    void print_status();
    void print_data();
    void print_dist_heaps();
    void print_point(const size_t p);
private:
    size_t n,d,k;     //number of rows/instances/points in the data set
    vector<vector<double>> P;   //original data to read from
    set<size_t> indecies;       // the full index set [0,n-1]
    set<size_t> is;             // the order that centers are selected
    map<size_t,center> centers; //|used for greedy permutation algorithm| = k
    
    vector<vector<size_t>> servedby; //list for maintaining old clusters that served
    vector<pair<size_t,double>> max_dists;           //max heap for all pip_alphas
    
    //keep all dist calculations in a fancy O(1) lookup, ins, delete heap ?
    unordered_map<pkey,double> comp_dists;
};
#endif	/* NN_H */

