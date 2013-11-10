/* 
 * File:   sb.h
 * Author: tbecker
 *
 * Created on November 4, 2013, 8:47 PM
 */
#ifndef sb_H
#define	sb_H
#include <vector>

using namespace std;

class sb {
public:
    sb(size_t n, size_t d, vector<vector<double>> m); //standard constructor
    sb(const sb&); //copy constructor
    virtual ~sb(); //destructor
    double dist(size_t p1, size_t p2);
    vector<double> minimum(vector<vector<double>> s);
private:
    size_t n;
    size_t d;
    vector<vector<double>> m;
};

#endif	/* sb_H */

