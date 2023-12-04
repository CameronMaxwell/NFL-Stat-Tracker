/**
 * @file Leaderboard.cpp
 * @author Cameron Maxwell
 * @brief Definition of the Leaderboard class This file contains the definition of the Leaderboard class, which is used for displaying and managing a leaderboard in a sports statistics application.
 * @version 1.0
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>
#include <Wt/WEnvironment.h>
#include <Wt/WBreak.h>
#include <Wt/WPushButton.h>
#include "Leaderboard.h"
#include "Wt/WLineEdit.h"
#include "Wt/WPopupMenu.h"
#include "Wt/WPopupMenuItem.h"
#include <algorithm>
#include <vector>
#include <memory>
#include <string>

#include "JsonDataManager.h"
#include <Wt/Json/Parser.h>
#include <Wt/Json/Object.h>
#include <Wt/Json/Serializer.h>
#include <Wt/Json/Array.h>
#include <Wt/Json/Value.h>

using namespace std;
using namespace Wt;

/**
 * @brief Construct a new Leaderboard:: Leaderboard object
 * 
 * @param loggedInUser 
 */

Leaderboard::Leaderboard(const User& loggedInUser) : loggedInUser_(loggedInUser) {
    
    addWidget(make_unique<Wt::WText>("<div style='text-align:center; font-size: 24px; font-weight: bold;'>Gridiron StatTrack</div>"));

    addWidget(make_unique<Wt::WBreak>());
    auto searchField = addNew<WLineEdit>();
    searchField->setMargin(2, Wt::Side::Left);
    searchField->setWidth(150);
    searchButton_ = addNew<WPushButton>("Search");
    searchButton_->setMargin(15, Wt::Side::Left);

    compareButton_ = addNew<Wt::WPushButton>("Compare");
    compareButton_->setMargin(75, Wt::Side::Left);
    compareButton_->clicked().connect(this, &Leaderboard::onCompareSwitch);

    favouritesButton_ = addNew<Wt::WPushButton>("Favourites");
    favouritesButton_->setMargin(75, Wt::Side::Left);
    favouritesButton_->clicked().connect(this, &Leaderboard::onFavouritesSwitch);

    helpButton_ = addNew<Wt::WPushButton>("Help Page");
    helpButton_->setMargin(75, Wt::Side::Left);
    helpButton_->clicked().connect(this, &Leaderboard::onHelpSwitch);

    logoutButton_ = addNew<Wt::WPushButton>("Logout");
    logoutButton_->setMargin(75, Wt::Side::Left);
    logoutButton_->clicked().connect(this, &Leaderboard::onLogoutSwitch);

    bettingTrack_ = addNew<Wt::WPushButton>("Betting Tracker");
    bettingTrack_->setMargin(75, Wt::Side::Left);
    bettingTrack_->clicked().connect(this, &Leaderboard::onBettingSwitch);

    Wt::WPushButton *dropdownButton = addNew<Wt::WPushButton>("Category");
    dropdownButton->setStyleClass("btn btn-default dropdown-toggle");
    dropdownButton->setMargin(75, Wt::Side::Left);

    
    auto popup = std::make_unique<Wt::WPopupMenu>();
    popup->addItem("Passing");
    popup->addItem("Rushing");
    popup->addItem("Receiving");

    // Attach the popup to the button
    dropdownButton->setMenu(std::move(popup));

    // Optional: handle menu item clicks
    dropdownButton->menu()->itemSelected().connect([=](Wt::WMenuItem *item) {
        handleItemSelected(item);
    });

    addWidget(std::make_unique<Wt::WBreak>());
    addWidget(std::make_unique<Wt::WBreak>());


    JsonDataManager jsonManager("./DatasetsNFL/Passing_2022.json");
    Wt::Json::Array playerArray = jsonManager.readData();

    playerTable = addNew<Wt::WTable>();
    playerTable->setWidth("100%");

    playerTable->elementAt(0, 0)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Rank</div>"));
    playerTable->elementAt(0, 1)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Name</div>"));
    playerTable->elementAt(0, 2)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Yds</div>"));
    playerTable->elementAt(0, 3)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>TDs</div>"));
    playerTable->elementAt(0, 4)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Team</div>"));
    playerTable->elementAt(0, 5)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Position</div>"));
    playerTable->elementAt(0, 6)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Add Favourite</div>"));

    for ( Wt::Json::Object& player: playerArray) {
        Leaderboard::addPlayerRow(playerTable, player["Rk"].toString(), player["Player"].toString(), player["Yds"].toString(), player["TD"].toString(), player["Tm"].toString(), player["Pos"].toString());
    }

    cout << loggedInUser_.getUsername() << " USERNAME" << endl;
    cout << loggedInUser_.getPassword() << " PASSWORD" << endl;


    searchButton_->clicked().connect([=] {
        searchSubmit(playerTable, searchField->text().toUTF8());
    });
}

/**
 * @brief Adds a row of players to the table, makes it pretty.
 * 
 * @param table 
 * @param rank 
 * @param player 
 * @param yards 
 * @param tds 
 * @param team 
 * @param position 
 */

void Leaderboard::addPlayerRow(Wt::WTable* table, std::string rank, std::string player, std::string yards, std::string tds, std::string team, std::string position) {
    int row = table->rowCount();
    table->elementAt(row, 0)->addWidget(make_unique<Wt::WText>(rank));
    table->elementAt(row, 0)->setAttributeValue("style", "border: 1px solid rgb(211, 211, 211)");
    table->elementAt(row, 1)->addWidget(make_unique<Wt::WText>(player));
    table->elementAt(row, 1)->setAttributeValue("style", "border: 1px solid rgb(211, 211, 211);");
    table->elementAt(row, 2)->addWidget(make_unique<Wt::WText>(yards));
    table->elementAt(row, 2)->setAttributeValue("style", "border: 1px solid rgb(211, 211, 211);");
    table->elementAt(row, 3)->addWidget(make_unique<Wt::WText>(tds));
    table->elementAt(row, 3)->setAttributeValue("style", "border: 1px solid rgb(211, 211, 211);");
    table->elementAt(row, 4)->addWidget(make_unique<Wt::WText>(team));
    table->elementAt(row, 4)->setAttributeValue("style", "border: 1px solid rgb(211, 211, 211);");
    table->elementAt(row, 5)->addWidget(make_unique<Wt::WText>(position));
    table->elementAt(row, 5)->setAttributeValue("style", "border: 1px solid rgb(211, 211, 211);");
    table->elementAt(row, 6)->addWidget(make_unique<Wt::WPushButton>("Add Favourite"));
    table->elementAt(row, 6)->clicked().connect(std::bind(&Leaderboard::addFavourite, this, player, team, position));
    table->elementAt(row, 6)->setAttributeValue("style", "border: 1px solid rgb(211, 211, 211);");

    for (int col = 0; col < 6; ++col) {
        auto cell = table->elementAt(row, col);

        // Attach a click event listener to each cell
        cell->clicked().connect([=] {
            handleColClick(table, col);
        });
    }
}

/**
 * @brief Handles the event when a column is clicked, highlights and sorts by the selected column.
 * 
 * @param table 
 * @param col 
 */

void Leaderboard::handleColClick(Wt::WTable* table, int col) {
        // Clear previous highlights
        for (int r = 0; r < table->rowCount(); ++r) {
            for (int c = 0; c < 6; ++c) {
                table->elementAt(r, c)->decorationStyle().setBackgroundColor(Wt::WColor());
            }
        }

        // Highlight the selected column
        for (int row = 1; row < table->rowCount(); ++row) {
            table->elementAt(row, col)->decorationStyle().setBackgroundColor(Wt::WColor(220,220,220));
        }

        sortTableByColumn(table, col);
}

/**
 * @brief Creates the leaderboard based on the selection from the dropdown.
 * 
 * @param item 
 */

void Leaderboard::handleItemSelected(Wt::WMenuItem* item) {
    std::string selection = item->text().toUTF8();

    playerTable->clear();
    playerTable->setWidth("100%");

    playerTable->elementAt(0, 0)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Rank</div>"));
    playerTable->elementAt(0, 1)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Name</div>"));
    playerTable->elementAt(0, 2)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Yds</div>"));
    playerTable->elementAt(0, 3)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>TDs</div>"));
    playerTable->elementAt(0, 4)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Team</div>"));
    playerTable->elementAt(0, 5)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Position</div>"));
    playerTable->elementAt(0, 6)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Add Favourite</div>"));

    if (selection == "Passing") {
        JsonDataManager jsonManager("./DatasetsNFL/Passing_2022.json");
        Wt::Json::Array playerArray = jsonManager.readData();

        for ( Wt::Json::Object& player: playerArray) {
            Leaderboard::addPlayerRow(playerTable, player["Rk"].toString(), player["Player"].toString(), player["Yds"].toString(), player["TD"].toString(), player["Tm"].toString(), player["Pos"].toString());
        }
    } else if (selection == "Rushing") {
        JsonDataManager jsonManager("./DatasetsNFL/Rushing_2022.json");
        Wt::Json::Array playerArray = jsonManager.readData();

        for ( Wt::Json::Object& player: playerArray) {
            Leaderboard::addPlayerRow(playerTable, player["Rk"].toString(), player["Player"].toString(), player["Yds"].toString(), player["TD"].toString(), player["Tm"].toString(), player["Pos"].toString());
        }
    } else {
        JsonDataManager jsonManager("./DatasetsNFL/Receiving_2022.json");
        Wt::Json::Array playerArray = jsonManager.readData();

        for ( Wt::Json::Object& player: playerArray) {
            Leaderboard::addPlayerRow(playerTable, player["Rk"].toString(), player["Player"].toString(), player["Yds▼"].toString(), player["TD"].toString(), player["Tm"].toString(), player["Pos"].toString());
        }
    }
}

/**
 * @brief Adds a player to the user's favourites list.
 * 
 * @param name 
 * @param team 
 * @param position 
 */

void Leaderboard::addFavourite(std::string name, std::string team, std::string position) {

    JsonDataManager jsonManager("UserData.json");
    Wt::Json::Array usersArray = jsonManager.readData();

    Wt::Json::Object favourite;

    for ( Wt::Json::Object& user: usersArray) {
        if (user["username"] == loggedInUser_.getUsername().data()) {

            Wt::Json::Array& favouritesArray = user["favourites"];
            int betCount = favouritesArray.size();

            favourite["name"] = name.data(); 
            favourite["team"] = team.data();
            favourite["pos"] = position.data();

            favouritesArray.push_back(favourite);

            jsonManager.writeData(usersArray);

            doJavaScript("alert('SUCCESS: Player was added to your favourites');");
            break;
        }
    }
}

/**
 * @brief Algorithm that sorts the leaderboard by column.
 * 
 * @param table 
 * @param columnIndex 
 */

void Leaderboard::sortTableByColumn(Wt::WTable* table, int columnIndex) {

    searchSubmit(table, "");

    // Vector to store the text from each cell and the row index
    std::vector<std::pair<int, std::string>> sortData;

    // Extract data from the table
    for (int row = 1; row < table->rowCount(); ++row) {
        Wt::WTableCell* cell = table->elementAt(row, columnIndex);
        Wt::WWidget* widget = cell->widget(0);
        if (widget) {  // Check if the cell or widget is not hidden
            Wt::WText* textWidget = dynamic_cast<Wt::WText*>(widget);
            if (textWidget) {
                std::string cellText = textWidget->text().toUTF8();
                sortData.emplace_back(row, cellText);
            }
        }
    }

    // Sort the data
    auto comparator = [columnIndex](const auto& a, const auto& b) {
        if (columnIndex == 1 || columnIndex == 4 || columnIndex == 5) { // Alphabetical sort for team names
            return a.second < b.second;
        } else if (columnIndex == 0) { // Numeric sort for other columns
            return std::stoi(a.second) < std::stoi(b.second);
        } else {
            return std::stoi(a.second) > std::stoi(b.second);
        }
    };
    std::sort(sortData.begin(), sortData.end(), comparator);

    // Temporary vector to hold the rows
    std::vector<std::unique_ptr<Wt::WWidget>> tempRowWidgets;

    // Swap the contents of each cell based on the sorted order
    for (size_t i = 0; i < sortData.size(); ++i) {
        tempRowWidgets.clear();
        for (int col = 0; col < table->columnCount(); ++col) {
            // Move each cell's widget to the temporary vector
            tempRowWidgets.push_back(table->elementAt(sortData[i].first, col)->removeWidget(table->elementAt(sortData[i].first, col)->widget(0)));
        }
        for (int col = 0; col < table->columnCount(); ++col) {
            // Move the widget from the temporary vector to the correct place in the table
            table->elementAt(i + 1, col)->addWidget(std::move(tempRowWidgets[col]));
        }
    }
}

/**
 * @brief Takes the search query and filters the leaderboard.
 * 
 * @param playerTable 
 * @param query 
 */

void Leaderboard::searchSubmit(Wt::WTable* playerTable, string query) {
    for (int row = 1; row < playerTable->rowCount(); ++row) {
        Wt::WWidget* widget = playerTable->elementAt(row, 1)->widget(0);
        Wt::WText* textWidget = dynamic_cast<Wt::WText*>(widget);
        if (textWidget) {
            std::string playerName = textWidget->text().toUTF8();
            if (playerName.find(query) != std::string::npos) {
                playerTable->rowAt(row)->show();
            } else {
                playerTable->rowAt(row)->hide();
            }
        }
    }
}

/**
 * @brief Sends the signal to GridironApplication to switch to help page.
 * 
 */

void Leaderboard::onHelpSwitch() {
    this->clear();
    switchToHelpSignal.emit(loggedInUser_);
}

/**
 * @brief Sends the signal to GridironApplication to switch to favourites page.
 * 
 */

void Leaderboard::onFavouritesSwitch() {
    this->clear();
    switchToFavouritesSignal.emit(loggedInUser_);
}

/**
 * @brief Sends the signal to GridironApplication to switch to logout page.
 * 
 */

void Leaderboard::onLogoutSwitch() {
    this->clear();
    switchToLoginSignal.emit();
}

/**
 * @brief Sends the signal to GridironApplication to switch to compare tool.
 * 
 */

void Leaderboard::onCompareSwitch() {
    this->clear();
    switchToCompareSignal.emit(loggedInUser_);
}

/**
 * @brief Sends the signal to GridironApplication to switch to search signal.
 * 
 */

void Leaderboard::onSearchSwitch() {
    this->clear();
    switchToSearchSignal.emit();
}

/**
 * @brief Sends the signal to GridironApplication to switch to betting tracker.
 * 
 */

void Leaderboard::onBettingSwitch() {
    this->clear();
    switchToBettingSignal.emit(loggedInUser_);
}

/**
 * @brief Sets the current logged in user.
 * 
 * @param user 
 */

void Leaderboard::setLoggedInUser(const User& user) {
    loggedInUser_ = user;
    // Now you can access the logged-in user's data using loggedInUser_ in other functions.
}



Leaderboard::~Leaderboard() {};
