//
// Created by savas on 18.02.2018.
//

#ifndef FFT_TRANSITION_H
#define FFT_TRANSITION_H
#include <iostream>


using namespace std;

class transition {
public:
    string state;
    string input;
    string next_state;
    string output;

    bool operator<(const transition & p) const;
	transition operator=(const transition & t) const; // NOLINT
	bool operator==(const transition & other) const;

};



#endif //FFT_TRANSİTİON_H
