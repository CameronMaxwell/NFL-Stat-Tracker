/**
 * @file RegisterWidget.h
 * @author Cameron Maxwell.
 * @brief This is the header file for the register widget which allows a user to create an account.
 * @version 1.0
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _REGISTERWIDGET_
#define _REGISTERWIDGET_

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WLineEdit.h>
#include <Wt/WBreak.h>
#include <Wt/WPushButton.h>
#include <Wt/Json/Array.h>
#include <Wt/Json/Value.h>
#include <Wt/WWidget.h>
#include "JsonDataManager.h"

class RegisterWidget : public Wt::WContainerWidget
{
public:
    RegisterWidget(); // Constructor
    ~RegisterWidget(); // Destructor

    Wt::Signal<> switchToLoginSignal;
    Wt::Signal<> switchToRegisterSignal;
    

private:
    Wt::WText        *title_; 
    Wt::WLineEdit    *emailBox_; // Text box used to read a users email
    Wt::WLineEdit    *usernameBox_; // Text box used to read a users username
    Wt::WLineEdit    *passwordBox_; // Text box used to read a users password
    Wt::WLineEdit    *passwordConfirmBox_; // Text box used to read a users password
    Wt::WPushButton  *registerButton_; // Button used to start new game
    
    Wt::Json::Value  userData;
    Wt::Json::Array  usersArray;

    void checkRegister(); // used to make sure the user credentials are correct
    bool checkUsed(std::string field, std::string input);
    void onLoginSwitch();
};

#endif // _REGISTERWIDGET_
