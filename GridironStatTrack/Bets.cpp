/**
 * @file Bets.cpp
 * @author Cameron Maxwell
 * @brief This class creates a bet object to store bet info
 * @version 1.0
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <string>
#include <vector>
#include "Bets.h"

using namespace std;

/**
 * @brief Construct a new Bet:: Bet object
 * 
 * @param setOdds 
 * @param setWager 
 * @param setLegs 
 * @param setSuccess 
 */
Bet::Bet(float setOdds, float setWager, string setLegs, bool setSuccess){
    odds = setOdds;
    wager = setWager;
    legs = setLegs;
    success = setSuccess;
}

/**
 * @brief Getter for odds
 * 
 * @return float 
 */
float Bet::getOdds() {
    return odds;
}

/**
 * @brief Getter for wager
 * 
 * @return float 
 */
float Bet::getWager() {
    return wager;
}

/**
 * @brief Getter for legs
 * 
 * @return std::string 
 */
std::string Bet::getLegs() {
    return legs;
}

/**
 * @brief Getter for success
 * 
 * @return true 
 * @return false 
 */
bool Bet::getSuccess() {
    return success;
}
