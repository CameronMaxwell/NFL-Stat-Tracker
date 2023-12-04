/**
 * @file ComparisonTool.h
 * @author Cameron Maxwell
 * @brief Header file for ComparisonTool.cpp
 * @version 1.0
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _COMPARISONTOOL_
#define _COMPARISONTOOL_

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WEnvironment.h>
#include <Wt/WText.h>
#include <Wt/WCheckBox.h>
#include <Wt/WLineEdit.h>
#include <Wt/WSpinBox.h>
#include "User.h"

class ComparisonTool : public Wt::WContainerWidget
{
public:
  ComparisonTool(const User& loggedInUser);
  ~ComparisonTool();

  Wt::Signal<const User&> switchToLeaderboardSignal;
  void setLoggedInUser(const User& user);

private:
  void createBarGraph(const Wt::WString& playerName, int touchdowns, int yards, int interceptions);
  void onMainSwitch();
  void onSubmit();
  User loggedInUser_;

  // Add member variables for input fields
    Wt::WLineEdit* playerNameEdit_;
    Wt::WLineEdit* touchdownsEdit_;
    Wt::WLineEdit* yardsEdit_;
    Wt::WLineEdit* interceptionsEdit_;

};

#endif
