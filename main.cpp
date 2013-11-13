/* 
 * File:   main.cpp
 * Author: tbecker
 *
 * Created on November 4, 2013, 8:54 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

/*
 * main nn command line program with arguments
 */
int main(int argc, char** argv) {
    string csv_in_file(argv[0]); //argv[0] is the program name, 1+ is args
    cout << csv_in_file << endl;
    return 0;
}

