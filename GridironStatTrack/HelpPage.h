/**
 * @file HelpPage.h
 * @author Cameron Maxwell
 * @brief The header file for the help page, used to help new users
 * @version 1.0
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _HELPPAGEWIDGET_
#define _HELPPAGEWIDGET_

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include "User.h"

class HelpPage : public Wt::WContainerWidget
{
public:
  HelpPage(const User& loggedInUser);
  ~HelpPage();

  Wt::Signal<const User&> switchToLeaderboardSignal;

  void setLoggedInUser(const User& user);

private:
  Wt::WText     *aboutInfo_;
  Wt::WText     *howToUse_;

  User loggedInUser_;

  void aboutUs();
  void howToUse();
  void onMainSwitch();
};

#endif
