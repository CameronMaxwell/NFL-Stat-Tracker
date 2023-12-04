/**
 * @file User.h
 * @author Cameron Maxwell
 * @brief The header file for the user class which holds a user's information
 * @version 1.0
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _USER_
#define _USER_

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Bets.h"


using namespace std;

class User {
public:
    // Constructor
    User(std::string email_in, std::string username_in, std::string password_in);

    void setEmail(std::string email_in);
    void setUsername(std::string username_in);
    void setPassword(std::string password_in);
    void addBet(Bet newBet);

    void removeFavourite(int index);

    std::string getEmail();
    std::string getUsername();
    std::string getPassword();
    std::vector<Bet> getBets();



private:
    std::string email;
    std::string username;
    std::string password;
    std::vector<Bet> userBets;

};

#endif
