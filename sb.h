/* 
 * File:   sb.h
 * Author: tbecker
 *
 * Created on November 4, 2013, 8:47 PM
 */
#ifndef sb_H
#define	sb_H
#include <array>

using namespace std;

template <class T, unsigned I, unsigned J>
using matrix = array<array<T, J>, I>;

class sb {
public:
    sb();
    sb(const sb& orig);
    virtual ~sb();
    double dist(matrix<double,1,4> i, matrix<double,1,4> j);
    matrix<double,1,4> minimum(matrix<double,2,4>);
private:
    
};

#endif	/* sb_H */

