/* 
 * File:   c11timer.h
 * Author: tbecker
 *
 * Created on November 13, 2013, 1:54 PM
 */

#ifndef C11TIMER_H
#define	C11TIMER_H
#include <chrono>
#include <vector>

using namespace std;
using namespace chrono::_V2;

class C11Timer {
public:
    C11Timer();
    C11Timer(const C11Timer& orig);
    virtual ~C11Timer();
    void ping();
    steady_clock::duration diff();
    double ms();
    double ns();
private:
    int i = 0;
    vector<steady_clock::time_point> t = {steady_clock::now(),steady_clock::now()};
};

#endif	/* C11TIMER_H */

