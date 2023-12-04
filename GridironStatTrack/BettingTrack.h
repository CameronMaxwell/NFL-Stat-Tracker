/**
 * @file BettingTrack.h
 * @author Cameron Maxwell
 * @brief Header file for BettingTrack.cpp
 * @version 1.0
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _BETTINGTRACKWIDGET_
#define _BETTINGTRACKWIDGET_

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WCheckBox.h>
#include "User.h"

class BettingTrack : public Wt::WContainerWidget
{
public:
  BettingTrack(const User& loggedInUser);
  ~BettingTrack();

  Wt::Signal<const User&> switchToLeaderboardSignal;
  void setLoggedInUser(const User& user);

private:
  Wt::WLineEdit       *oddsEnter;
  Wt::WLineEdit       *wagerEnter;
  Wt::WCheckBox       *betSuccess;
  Wt::WLineEdit       *legsEnter;
  bool                 success;
  void addBetRow(Wt::WTable* table, Bet newBet);
  void onMainSwitch();
  void createBet(Wt::WTable* table);
  std::string removeZeroes(float value);
  User loggedInUser_;
};

#endif
