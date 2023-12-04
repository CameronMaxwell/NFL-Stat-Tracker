/**
 * @file Bets.h
 * @author Cameron Maxwell
 * @brief Header file for Bets.cpp
 * @version 1.0
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _BETOBJ_
#define _BETOBJ_


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Bet {
public:
    // Constructor
    Bet(float odds, float wager, string legs, bool success);

    float getOdds();
    float getWager();
    string getLegs();
    bool getSuccess();

private:
    float odds; 
    float wager;  
    string legs;  
    bool success;
};

#endif
