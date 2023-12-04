/**
 * @file GridironApplication.cpp
 * @author Cameron Maxwell
 * @brief The main application that controls, creates, and manages widgets.
 * @version 1.0
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "GridironApplication.h"
#include "RegisterWidget.h"
#include "LoginWidget.h"
#include "Leaderboard.h"
#include "HelpPage.h"
#include "BettingTrack.h"
#include "FavouritesWidget.h"
#include "ComparisonTool.h"

using namespace Wt;

/**
 * @brief Construct a new Gridiron Application:: Gridiron Application object
 * 
 * @param env 
 */
GridironApplication::GridironApplication(const Wt::WEnvironment& env)
  : WApplication(env)
{
    setCssTheme("polished");
    setTitle("Gridiron Stat Track"); 

 
    JsonDataManager jsonManager("UserData.json");
    auto loginWidget = std::make_unique<LoginWidget>();
    auto registerWidget = std::make_unique<RegisterWidget>();

    // Initially, add the LoginWidget to the root
    auto loginPage = root()->addWidget(std::make_unique<LoginWidget>());
    loginPage->switchToRegisterSignal.connect(this, &GridironApplication::onRegisterSwitch);
    loginPage->switchToLeaderboardSignal.connect(this, &GridironApplication::onLeaderboardSwitch);
}

/**
 * @brief Receives a signal and creates a login page, accepts signals from login page to switch to other pages.
 * 
 */
void GridironApplication::onLoginSwitch() {
    auto loginPage = root()->addWidget(std::make_unique<LoginWidget>());
    loginPage->switchToRegisterSignal.connect(this, &GridironApplication::onRegisterSwitch);
    loginPage->switchToLeaderboardSignal.connect(this, &GridironApplication::onLeaderboardSwitch);
}

/**
 * @brief Receives a signal and creates the main page, accepts signals from main page to switch to other pages.
 * 
 * @param user 
 */
void GridironApplication::onLoginSuccessful(const User& user) {
    // Now you have access to the logged-in user's data (user.getEmail(), user.getUsername(), etc.)
    auto mainPage = root()->addWidget(std::make_unique<Leaderboard>(user));  // Pass the User object
    mainPage->switchToLoginSignal.connect(this, &GridironApplication::onLoginSwitch);
    mainPage->switchToHelpSignal.connect(this, &GridironApplication::onHelpSwitch);
    mainPage->switchToBettingSignal.connect(this, &GridironApplication::onBettingSwitch);
}

/**
 * @brief Receives a signal and creates a register page, accepts signals from register page to switch to other pages.
 * 
 */
void GridironApplication::onRegisterSwitch() {
    auto registerPage = root()->addWidget(std::make_unique<RegisterWidget>());
    registerPage->switchToLoginSignal.connect(this, &GridironApplication::onLoginSwitch);
}

/**
 * @brief Receieves a signal and creates a main page, accepts signals from register page to switch to other pages.
 * 
 * @param loggedInUser 
 */
void GridironApplication::onLeaderboardSwitch(const User& loggedInUser) {
    auto mainPage = root()->addWidget(std::make_unique<Leaderboard>(loggedInUser));
    mainPage->switchToLoginSignal.connect(this, &GridironApplication::onLoginSwitch);
    mainPage->switchToHelpSignal.connect(this, &GridironApplication::onHelpSwitch);
    mainPage->switchToBettingSignal.connect(this, &GridironApplication::onBettingSwitch);
    mainPage->switchToFavouritesSignal.connect(this, &GridironApplication::onFavouritesSwitch);
    mainPage->switchToCompareSignal.connect(this, &GridironApplication::onCompareSwitch);
}

/**
 * @brief Receives a signal and creates a help page, accepts signal from help page to switch back to leaderboard.
 * 
 * @param loggedInUser 
 */
void GridironApplication::onHelpSwitch(const User& loggedInUser) {
    auto helpPage = root()->addWidget(std::make_unique<HelpPage>(loggedInUser));
    helpPage->switchToLeaderboardSignal.connect(this, &GridironApplication::onLeaderboardSwitch);
}

/**
 * @brief Receives a signal and creates a favourites page, accepts a signal from favourites page to switch back to leaderboard.
 * 
 * @param loggedInUser 
 */
void GridironApplication::onFavouritesSwitch(const User& loggedInUser) {
    auto favouritesPage = root()->addWidget(std::make_unique<FavouritesPage>(loggedInUser));
    favouritesPage->switchToLeaderboardSignal.connect(this, &GridironApplication::onLeaderboardSwitch);

}

/**
 * @brief Receives a signal from betting page to switch back to leaderboard.
 * 
 * @param loggedInUser 
 */
void GridironApplication::onBettingSwitch(const User& loggedInUser) {
    auto bettingPage = root()->addWidget(std::make_unique<BettingTrack>(loggedInUser));
    bettingPage->switchToLeaderboardSignal.connect(this, &GridironApplication::onLeaderboardSwitch);
}

/**
 * @brief Receieves a signal from compare page to switch back to leaderboard.
 * 
 * @param loggedInUser 
 */
void GridironApplication::onCompareSwitch(const User& loggedInUser) {
    auto comparePage = root()->addWidget(std::make_unique<ComparisonTool>(loggedInUser));
    comparePage->switchToLeaderboardSignal.connect(this, &GridironApplication::onLeaderboardSwitch);
}

/**
 * Destructor
*/
GridironApplication::~GridironApplication() {}
