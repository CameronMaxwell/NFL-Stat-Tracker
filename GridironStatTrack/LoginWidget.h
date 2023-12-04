/**
 * @file LoginWidget.h
 * @author Cameron Maxwell
 * @brief This is the header file for the login widget which creates a login page.
 * @version 1.0
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _LOGINWIDGET_
#define _LOGINWIDGET_

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WLineEdit.h>
#include <Wt/WBreak.h>
#include <Wt/WPushButton.h>
#include <Wt/Json/Array.h>
#include <Wt/Json/Value.h>
#include <Wt/WWidget.h>
#include "JsonDataManager.h"
#include "User.h"

class LoginWidget : public Wt::WContainerWidget
{
public:
    LoginWidget(); // Constructor
    ~LoginWidget(); // Destructor

    Wt::Signal<> switchToRegisterSignal;
    Wt::Signal<User> switchToLeaderboardSignal;
    Wt::Signal<User> loginSuccessfulSignal;

private:
    Wt::WText        *title_; 
    Wt::WLineEdit    *usernameBox_; // Text box used to read a users username
    Wt::WLineEdit    *passwordBox_; // Text box used to read a users password
    Wt::WPushButton  *loginButton_; // Button used to login
    
    Wt::Json::Value  userData;
    Wt::Json::Array  usersArray;

    bool checkLogin(); // used to make sure the user credentials are correct
    void onRegisterSwitch();
    void onLeaderboardSwitch();
};

#endif // _LOGINWIDGET_
