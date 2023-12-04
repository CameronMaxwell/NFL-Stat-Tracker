/**
 * @file RegisterWidget.cpp
 * @author Cameron Maxwell
 * @brief This is the custom register widget that is for users to create accounts.
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
#include "RegisterWidget.h"
#include "LoginWidget.h"

#include <Wt/Json/Parser.h>
#include <Wt/Json/Object.h>
#include <Wt/Json/Serializer.h>

using namespace Wt;
using namespace std;

/**
 * @brief Construct a new Register Widget:: Register Widget object
 * 
 */

RegisterWidget::RegisterWidget()
{

    Wt::Signal<> switchToLoginSignal;
    JsonDataManager jsonManager("UserData.json");
    setContentAlignment(AlignmentFlag::Center);
    doJavaScript("document.body.style.backgroundColor = '#FFFFFF';");

    auto image = addNew<Wt::WImage>("resources/GSLogo.png");
    image->resize(250, Wt::WLength::Auto);
    title_ = addNew<WText>("<h3>Welcome to Gridiron Stat Track<br></br> Register for an account below</h3>");

    // Text box used to read a users email
    addNew<WText>("<h5>Email</h5>");
    emailBox_ = addNew<WLineEdit>();
    emailBox_->setMaxLength(30);
    emailBox_->decorationStyle().border(Wt::Side::Top);
    emailBox_->setFocus();

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

    // Text box used to read a users password confirmation
    addNew<WText>("<h5>Confirm Password</h5>");
    passwordConfirmBox_ = addNew<WLineEdit>();
    passwordConfirmBox_->setMaxLength(30);
    passwordConfirmBox_->decorationStyle().border(Wt::Side::Top);
    passwordConfirmBox_->setFocus();
    addWidget(std::make_unique<Wt::WBreak>());
    addWidget(std::make_unique<Wt::WBreak>());
    
    // Button used to register
    registerButton_ = addNew<WPushButton>("Register");
    registerButton_->setMargin(5, Wt::Side::Left); 
    registerButton_->clicked().connect(this, &RegisterWidget::checkRegister);
    addWidget(std::make_unique<Wt::WBreak>());
    addWidget(std::make_unique<Wt::WBreak>());


    userData = jsonManager.readData();
    //usersArray = jsonManager.readData();
    usersArray = userData;

    //create button to switch to login page
    auto switchToLoginButton = addNew<Wt::WPushButton>("Switch to Login");
    switchToLoginButton->clicked().connect(this, &RegisterWidget::onLoginSwitch);
}


/**
 * @brief Checks if the information entered by the user is valid for an account./
 * 
 */
void RegisterWidget::checkRegister() {
    JsonDataManager jsonManager("UserData.json");

    std::string email = emailBox_->text().toUTF8();
    std::string username = usernameBox_->text().toUTF8();
    std::string password = passwordBox_->text().toUTF8();
    std::string passwordConfirm = passwordConfirmBox_->text().toUTF8();

    bool correct = true;
    // Check if email is already used, if it has @ symbol, and more than 5 letters
    if (email.length() < 5 || checkUsed("email", email) == true) {
        correct = false;
    }
    // Check if username used, more than 3 letters
    if (username.length() < 3 || checkUsed("username", username) == true) {
        correct = false;
    }
    // Check if password meets requiments (1 upper case, 1 lower, 1 number, 8 chars), and equivalent to confirm
    if (password.length() < 8) {
        correct = false;
    }

    // IF ALL TRUE THEN ADD THE USER AND BRING LOG THEM IN
    if (correct == true) {

        Wt::Json::Object newUser;
        newUser["email"] = email.data();
        newUser["username"] = username.data();
        newUser["password"] = password.data();
        newUser["bets"] = Wt::Json::Array();
        newUser["favourites"] = Wt::Json::Array();

        // Access the "users" array and append the new user
        usersArray.push_back(newUser);

        // Write the updated JSON data back to the file
        jsonManager.writeData(usersArray);

        RegisterWidget::onLoginSwitch();
        return;
    } else {
        doJavaScript("alert('ERROR: Please ensure your email, username, and password are correct');");
    }
    emailBox_->setText("");
    usernameBox_->setText("");
    passwordBox_->setText("");
    passwordConfirmBox_->setText("");
    // DISPLAY WHICH ONE IS WRONG OR ALREADY USED
};

/**
 * @brief Checks if the account has already been used
 * 
 * @param field 
 * @param input 
 * @return true 
 * @return false 
 */
bool RegisterWidget::checkUsed(std::string field, std::string input) {
    for (const Wt::Json::Value& user : usersArray) {
        Wt::Json::Object userObject = user;
    
        if (userObject.find(field) != userObject.end()) {
            if (userObject[field] == input) {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Sends a signal to GridironApplication to switch to the login page
 * 
 */
void RegisterWidget::onLoginSwitch() {
    this->clear();
    switchToLoginSignal.emit();
}

/**
 * Destructor
*/
RegisterWidget::~RegisterWidget() {};
