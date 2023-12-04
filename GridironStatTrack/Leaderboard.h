/**
 * @file Leaderboard.h
 * @author Cameron Maxwell
 * @brief The header file for the leaderboard widget.
 * @version 1.0
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _LEADERBOARDWIDGET_
#define _LEADERBOARDWIDGET_

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>
#include <Wt/WEnvironment.h>
#include <Wt/WBreak.h>
#include <Wt/WPushButton.h>
#include "User.h"

using namespace std;

class Leaderboard : public Wt::WContainerWidget
{
    
public:
    Leaderboard(const User& loggedInUser); //constructor
    ~Leaderboard();

    Wt::Signal<> switchToLoginSignal;
    Wt::Signal<const User&> switchToHelpSignal;
    Wt::Signal<const User&> switchToCompareSignal;
    Wt::Signal<> switchToSearchSignal;
    Wt::Signal<const User&> switchToBettingSignal;
    Wt::Signal<const User&> switchToFavouritesSignal;

    void setLoggedInUser(const User& user);

private:
    Wt::WPushButton *searchButton_;
    Wt::WPushButton *favouritesButton_;
    Wt::WPushButton *compareButton_;
    Wt::WPushButton *helpButton_;
    Wt::WPushButton *logoutButton_;
    Wt::WPushButton *bettingTrack_;

    Wt::WTable *playerTable;

    User loggedInUser_;

    void addPlayerRow(Wt::WTable* table, std::string rank, std::string player, std::string yards, std::string tds, std::string team, std::string position);
    void addFavourite(std::string name, std::string team, std::string position);
    void handleItemSelected(Wt::WMenuItem* item);
    void handleColClick(Wt::WTable* table, int col);
    void sortTableByColumn(Wt::WTable* table, int col);
    void searchSubmit(Wt::WTable* table, string query);
    void onLogoutSwitch();
    void onHelpSwitch();
    void onFavouritesSwitch();
    void onCompareSwitch();
    void onSearchSwitch();
    void onBettingSwitch();
};

#endif
