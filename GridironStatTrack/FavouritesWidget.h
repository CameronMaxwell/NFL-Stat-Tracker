/**
 * @file FavouritesWidget.h
 * @author Cameron Maxwell
 * @brief 
 * @version 0.1
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _FAVOURITESWIDGET_
#define _FAVOURITESWIDGET_

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WCheckBox.h>
#include <string>
#include "User.h"

using namespace std;

class FavouritesPage : public Wt::WContainerWidget
{
public:
  FavouritesPage(const User& loggedInUser);
  ~FavouritesPage();

  Wt::Signal<const User&> switchToLeaderboardSignal;
  void setLoggedInUser(const User& user);
  void addFavRow(Wt::WTable* table, int rank, std::string name, std::string team, std::string pos);

private:
    Wt::WTable          *favouritesTable;
    void onMainSwitch();
    User loggedInUser_;

    void removeFavourite(std::string name, std::string team, std::string pos);
};

#endif
