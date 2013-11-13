/* 
 * File:   c11timer.hpp
 * Author: tbecker
 *
 * Created on November 13, 2013, 11:08 AM
 * Pingable C++11 chrono timer with immutable stead_clock
 */

#ifndef C11TIMER_HPP
#define	C11TIMER_HPP
#include <iostream>
#include <chrono>

using namespace std;

class C11Timer {
public:
    C11Timer(){ 
        t[0] = chrono::_V2::steady_clock::now();
        t[1] = chrono::_V2::steady_clock::now();
    }
    C11Timer(const C11Timer&);
    virtual ~C11Timer();
    void start(){ t[0] = chrono::_V2::steady_clock::now(); };
    void stop() { t[1] = chrono::_V2::steady_clock::now(); }
    void diff() { return t[1]-t[0]; };
private:
    vector<auto> t(2);
};


#endif	/* C11TIMER_HPP */

