/**
 * @file GridironApplication.h
 * @author Cameron Maxwell
 * @brief The header file for the main application that controls which widget is currently shown.
 * @version 1.0
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include "User.h"

/**
 * @brief An application that runs and manages which widgets are visible.
 * 
 */
class GridironApplication : public Wt::WApplication
{
public:
  GridironApplication(const Wt::WEnvironment& env);  // Constructor
  ~GridironApplication();  // Destructor

private:
  Wt::WText     *title_; // Application title
  void onLoginSwitch();
  void onRegisterSwitch();
  void onLeaderboardSwitch(const User& user);
  void onLogoutSwitch();
  void onHelpSwitch(const User& loggedInUser);
  void onFavouritesSwitch(const User& loggedInUser);
  void onCompareSwitch(const User& loggedInUser);
  void onSearchSwitch();
  void onLoginSuccessful(const User& user);
  void onBettingSwitch(const User& user);
};
