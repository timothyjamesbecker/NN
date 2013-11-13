/* 
 * File:   timer.hpp
 * Author: tbecker
 *
 * Created on November 13, 2013, 11:08 AM
 * Pingable C++11 chrono timer with immutable stead_clock
 */

#ifndef TIMER_HPP
#define	TIMER_HPP
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
    void ping(){  };
    void diff(){  };
private:
    vector<auto> t(2);
};


#endif	/* TIMER_HPP */

