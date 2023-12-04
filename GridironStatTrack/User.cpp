/**
 * @file User.cpp
 * @author Cameron Maxwell
 * @brief This is the user class that stores a user's personal data.
 * @version 1.0
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "User.h"

using namespace std;

/**
 * @brief Construct a new User:: User object
 * 
 * @param email_in 
 * @param username_in 
 * @param password_in 
 */
User::User(std::string email_in, std::string username_in, std::string password_in){
    email = email_in;
    username = username_in;
    password = password_in;
    userBets = {};
}

/**
 * @brief Sets the email of the user
 * 
 * @param email_in 
 */
void User::setEmail(std::string email_in) {
    email = email_in;
}

/**
 * @brief Sets the username of the user
 * 
 * @param username_in 
 */
void User::setUsername(std::string username_in) {
    username = username_in;
}

/**
 * @brief Sets the password of the user
 * 
 * @param password_in 
 */
void User::setPassword(std::string password_in) {
    password = password_in;
}

/**
 * @brief Adds a bet to the user's bet list
 * 
 * @param newBet 
 */
void User::addBet(Bet newBet) {
    userBets.push_back(newBet);
}


/**
 * @brief Returns the user's email
 * 
 * @return std::string 
 */
std::string User::getEmail() {
    return email;
}

/**
 * @brief Returns the user's username
 * 
 * @return std::string 
 */
std::string User::getUsername() {
    return username;
}

/**
 * @brief Returns the user's password
 * 
 * @return std::string 
 */
std::string User::getPassword() {
    return password;
}

/**
 * @brief Returns the user's bet list
 * 
 * @return std::vector<Bet> 
 */
std::vector<Bet> User::getBets() {
    return userBets;
}
