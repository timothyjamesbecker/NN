/* 
 * File:   c11timer.cpp
 * Author: tbecker
 * 
 * Created on November 13, 2013, 1:54 PM
 */
#include <cmath>
#include "c11timer.h"

C11Timer::C11Timer() {}

C11Timer::C11Timer(const C11Timer& orig) {}

C11Timer::~C11Timer() {}

void C11Timer::ping(){ i=(i==0?1:0); t[i] = chrono::_V2::steady_clock::now(); }

chrono::_V2::steady_clock::duration C11Timer::diff(){ return t[1]-t[0]; };
double C11Timer::ms(){ return abs(chrono::duration<double,milli>(diff()).count()); }
double C11Timer::ns(){ return abs(chrono::duration<double,nano>(diff()).count()); }