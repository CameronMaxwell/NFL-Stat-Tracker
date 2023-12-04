/**
 * @file FavouritesWidget.cpp
 * @author Cameron Maxwell
 * @brief This custom widget displays and tracks the current user's favourites.
 * @version 1.0
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WTable.h>
#include <string.h>
#include "JsonDataManager.h"
#include <Wt/WCheckBox.h>
#include "FavouritesWidget.h"
#include <Wt/Json/Parser.h>
#include <Wt/Json/Object.h>
#include <Wt/Json/Serializer.h>
#include <Wt/Json/Array.h>
#include <Wt/Json/Value.h>

/**
 * @brief Construct a new Favourites Page:: Favourites Page object
 * 
 * @param loggedInUser 
 */
FavouritesPage::FavouritesPage(const User& loggedInUser) : loggedInUser_(loggedInUser) {
    
    // Add page title, bold and center
    addNew<Wt::WText>("<div style='text-align:center; font-size: 24px; font-weight: bold;'>Favourites Page!</div>");
    addWidget(std::make_unique<Wt::WBreak>());
    addWidget(std::make_unique<Wt::WBreak>());

    // Add centered subtitle
    addNew<Wt::WText>("<div style='text-align:center;'>Welcome to the Gridiron StatTrack Favourites Page!</div>");
    addWidget(std::make_unique<Wt::WBreak>());

    // Add second centered subtitle
    addNew<Wt::WText>("<div style='text-align:center;'>Here you will find a table of all your favourited players, with access to all their stats!.</div>");
    addWidget(std::make_unique<Wt::WBreak>());
    addWidget(std::make_unique<Wt::WBreak>());

      

    auto backButton = addNew<Wt::WPushButton>("Back to Main Menu.");
    backButton->setMargin(50, Wt::Side::Left);
    backButton->setMargin(0, Wt::Side::Right);
    backButton->clicked().connect(this, &FavouritesPage::onMainSwitch);
    addWidget(std::make_unique<Wt::WBreak>());
    addWidget(std::make_unique<Wt::WBreak>());


    Wt::WTable *favouritesTable = addNew<Wt::WTable>();
    favouritesTable->setWidth("100%");
    favouritesTable->addStyleClass("table-bordered");
    favouritesTable->setAttributeValue("style", "border-collapse: collapse;");

    favouritesTable->elementAt(0,0)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Rank</div>"));
    favouritesTable->elementAt(0,1)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Player Name</div>"));
    favouritesTable->elementAt(0,2)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Team</div>"));
    favouritesTable->elementAt(0,3)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Position</div>"));
    favouritesTable->elementAt(0,4)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Favourite</div>"));

    JsonDataManager jsonManager("UserData.json");
    Wt::Json::Array usersArray = jsonManager.readData();

    Wt::Json::Object fav;

    for ( Wt::Json::Object& user: usersArray) {
        if (user["username"] == loggedInUser_.getUsername().data()) {
            Wt::Json::Array& favsArray = user["favourites"];

            int rank = 0;
            for (Wt::Json::Object& fav: favsArray) {
                rank = rank + 1;
                addFavRow(favouritesTable, rank, fav["name"], fav["team"], fav["pos"]);
            }
        }
    }
}

/**
 * @brief Adds a row to the favourite's list table
 * 
 * @param table 
 * @param rank 
 * @param name 
 * @param team 
 * @param pos 
 */
void FavouritesPage::addFavRow(Wt::WTable* table, int rank, std::string name, std::string team, std::string pos) {
    int row = table->rowCount();

    table->elementAt(row, 0)->addWidget(make_unique<Wt::WText>(std::to_string(rank)));
    table->elementAt(row, 0)->setAttributeValue("style", "border: 1px solid rgb(211, 211, 211)");
    table->elementAt(row, 1)->addWidget(make_unique<Wt::WText>(name));
    table->elementAt(row, 1)->setAttributeValue("style", "border: 1px solid rgb(211, 211, 211)");
    table->elementAt(row, 2)->addWidget(make_unique<Wt::WText>(team));
    table->elementAt(row, 2)->setAttributeValue("style", "border: 1px solid rgb(211, 211, 211)");
    table->elementAt(row, 3)->addWidget(make_unique<Wt::WText>(pos));
    table->elementAt(row, 3)->setAttributeValue("style", "border: 1px solid rgb(211, 211, 211)");
    table->elementAt(row, 4)->addWidget(make_unique<Wt::WPushButton>("Remove"));
    table->elementAt(row, 4)->clicked().connect(std::bind(&FavouritesPage::removeFavourite, this, name, team, pos));
    table->elementAt(row, 4)->setAttributeValue("style", "border: 1px solid rgb(211, 211, 211);");

}

/**
 * @brief Sends a signal to GridironApplication to switch back to the main page.
 * 
 */
void FavouritesPage::removeFavourite(std::string name, std::string team, std::string pos) {
    JsonDataManager jsonManager("UserData.json");
    Wt::Json::Array usersArray = jsonManager.readData();

    for (Wt::Json::Object& user: usersArray) {
        if (user["username"] == loggedInUser_.getUsername().data()) {

            Wt::Json::Array& favouritesArray = user["favourites"];
            Wt::Json::Array newFavouritesArray = Wt::Json::Array();

            for (Wt::Json::Object& fav: favouritesArray) {
                if (fav["name"] != name.data()) {
                    newFavouritesArray.push_back(fav);
                }
            }

            user["favourites"] = newFavouritesArray;

            jsonManager.writeData(usersArray);

            doJavaScript("alert('SUCCESS: Player was successfully removed');");
            break;
        }
    }
}


void FavouritesPage::onMainSwitch(){
    this->clear();
    switchToLeaderboardSignal.emit(loggedInUser_);
}


FavouritesPage::~FavouritesPage() {};
