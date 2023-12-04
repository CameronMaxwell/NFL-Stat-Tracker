/**
 * @file LoginWidget.cpp
 * @author Cameron Maxwell
 * @brief This is the custom login widget which prompts the user to login.
 * @version 1.0
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <set>
#include <Wt/WObject.h>
#include <Wt/WCssDecorationStyle.h>
#include "LoginWidget.h"
#include "RegisterWidget.h"
#include "Wt/WImage.h"

#include <Wt/Json/Parser.h>
#include <Wt/Json/Object.h>
#include <Wt/Json/Serializer.h>

using namespace Wt;
using namespace std;

/**
 * @brief Construct a new Login Widget:: Login Widget object
 * 
 */

LoginWidget::LoginWidget()
{

    JsonDataManager jsonManager("UserData.json");
    setContentAlignment(AlignmentFlag::Center);
    doJavaScript("document.body.style.backgroundColor = '#FFFFFF';");

    auto image = addNew<Wt::WImage>("resources/GSLogo.png");
    image->resize(250, Wt::WLength::Auto);

    // Text box used to read a users username
    addNew<WText>("<h5>Username</h5>");
    usernameBox_ = addNew<WLineEdit>();
    usernameBox_->setMaxLength(30);
    usernameBox_->decorationStyle().border(Wt::Side::Top);
    usernameBox_->setFocus();

    // Text box used to read a users password
    addNew<WText>("<h5>Password</h5>");
    passwordBox_ = addNew<WLineEdit>();
    passwordBox_->setMaxLength(30);
    passwordBox_->decorationStyle().border(Wt::Side::Top);
    passwordBox_->setFocus(); 
    
    // Button used to login
    loginButton_ = addNew<WPushButton>("Login");
    loginButton_->setMargin(5, Wt::Side::Left); 
    loginButton_->clicked().connect(this, &LoginWidget::onLeaderboardSwitch);
    addWidget(std::make_unique<Wt::WBreak>());
    addWidget(std::make_unique<Wt::WBreak>());


    userData = jsonManager.readData();
    //usersArray = jsonManager.readData();
    usersArray = userData;

    WPushButton* switchToRegisterButton = addNew<WPushButton>("Switch to Register");
    switchToRegisterButton->clicked().connect(this, &LoginWidget::onRegisterSwitch);
}


/**
 * @brief Checks the login the user entered to make sure it is valid
 * 
 * @return true 
 * @return false 
 */

bool LoginWidget::checkLogin() {
    std::string username = usernameBox_->text().toUTF8();
    std::string password = passwordBox_->text().toUTF8();

    bool correct = false;
    
    for (const Wt::Json::Value& user : usersArray) {
        Wt::Json::Object userObject = user;
    
        if (userObject.find("username") != userObject.end()) {
            if (userObject["username"] == username && userObject["password"] == password) {
                
                // LOG THE USER IN
                return true;
            }
        }
    }

    // IF ALL TRUE THEN ADD THE USER AND BRING LOG THEM IN
    if (correct == false) {
        doJavaScript("alert('ERROR: Please ensure your username and password are correct');");
    }
    usernameBox_->setText("");
    passwordBox_->setText("");
    return false;
};

/**
 * @brief Sends a signal to GridironApplication to switch to register page.
 * 
 */

void LoginWidget::onRegisterSwitch() {
    this->clear();
    switchToRegisterSignal.emit();
}

/**
 * @brief Checks if user login is valid, then sends signal to GridironApplication to switch to leaderboard page.
 * 
 */

void LoginWidget::onLeaderboardSwitch() {
    if (LoginWidget::checkLogin() == true) {

        User currentUser(usernameBox_->text().toUTF8(), usernameBox_->text().toUTF8(), passwordBox_->text().toUTF8());
        loginSuccessfulSignal.emit(currentUser);

        this->clear();
        switchToLeaderboardSignal.emit(currentUser);
    }
}

/**
 * Destructor
*/
LoginWidget::~LoginWidget() {};
