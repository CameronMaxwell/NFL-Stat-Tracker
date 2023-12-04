/**
 * @file BettingTrack.cpp
 * @author Cameron Maxwell
 * @brief This is the UI for the betting page of the application
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
#include <string.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <Wt/WCheckBox.h>
#include "BettingTrack.h"
#include "Bets.h"
#include "Wt/WTable.h"
#include "JsonDataManager.h"
#include <string>
#include <Wt/Json/Parser.h>
#include <Wt/Json/Object.h>
#include <Wt/Json/Serializer.h>
#include <Wt/Json/Array.h>
#include <Wt/Json/Value.h>

/**
 * @brief Construct a new Betting Track:: Betting Track object
 * 
 * @param loggedInUser 
 */
BettingTrack::BettingTrack(const User& loggedInUser) : loggedInUser_(loggedInUser) {
    // Add page title, bold and center
    addNew<Wt::WText>("<div style='text-align:center; font-size: 24px; font-weight: bold;'>Betting Tracker!</div>");
    addWidget(std::make_unique<Wt::WBreak>());
    addWidget(std::make_unique<Wt::WBreak>());

    // Add centered subtitle
    addNew<Wt::WText>("<div style='text-align:center;'>Welcome to the Gridiron StatTrack Betting Tracker!</div>");
    addWidget(std::make_unique<Wt::WBreak>());

    // Add second centered subtitle
    addNew<Wt::WText>("<div style='text-align:center;'>Here you can enter inforation about bets that you place and keep track of your winnings!.</div>");
    addWidget(std::make_unique<Wt::WBreak>());
    addWidget(std::make_unique<Wt::WBreak>());

    addNew<Wt::WText>("Please enter the odds (decimal form):");
    oddsEnter = addNew<Wt::WLineEdit>();
    oddsEnter->setPlaceholderText("Ex: 2.15");
    oddsEnter->setMargin(20, Wt::Side::Left);
    addWidget(std::make_unique<Wt::WBreak>());

    addNew<Wt::WText>("Please enter wager (in dollars):");
    wagerEnter = addNew<Wt::WLineEdit>();
    wagerEnter->setPlaceholderText("Ex: 10.00");
    wagerEnter->setMargin(20, Wt::Side::Left);
    addWidget(std::make_unique<Wt::WBreak>());

    addNew<Wt::WText>("Please describe the legs of the bet (brief description):");
    legsEnter = addNew<Wt::WLineEdit>();
    legsEnter->setPlaceholderText("Ex: Bills Moneyline vs Jets");
    legsEnter->setMargin(20, Wt::Side::Left);
    addWidget(std::make_unique<Wt::WBreak>());

    betSuccess = addNew<Wt::WCheckBox>("Was the bet successful?");
    addWidget(std::make_unique<Wt::WBreak>());


    // Add Back Button
    addWidget(std::make_unique<Wt::WBreak>());
    auto backButton = addNew<Wt::WPushButton>("Back to Main Menu.");
    backButton->setMargin(50, Wt::Side::Left);
    backButton->setMargin(0, Wt::Side::Right);
    backButton->clicked().connect(this, &BettingTrack::onMainSwitch);

    auto submitButton = addNew<Wt::WPushButton>("Submit Bet.");
    submitButton->setMargin(20, Wt::Side::Left); 

    Wt::WTable *betTable = addNew<Wt::WTable>();
    betTable->setWidth("100%");

    addWidget(std::make_unique<Wt::WBreak>());
    addWidget(std::make_unique<Wt::WBreak>());
    betTable->elementAt(0, 0)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Legs</div>"));
    betTable->elementAt(0, 1)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Odds</div>"));
    betTable->elementAt(0, 2)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Wager</div>"));
    betTable->elementAt(0, 3)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Success</div>"));
    betTable->elementAt(0, 4)->addWidget(make_unique<Wt::WText>("<div style='font-weight: bold;'>Payout</div>"));

    betTable->addStyleClass("table-bordered");
    betTable->setAttributeValue("style", "border-collapse: collapse;");

    submitButton->clicked().connect(std::bind(&BettingTrack::createBet, this, betTable));


    JsonDataManager jsonManager("UserData.json");
    Wt::Json::Array usersArray = jsonManager.readData();

    Wt::Json::Object bet;

    for ( Wt::Json::Object& user: usersArray) {
        if (user["username"] == loggedInUser_.getUsername().data()) {
            Wt::Json::Array& betsArray = user["bets"];
            int betCount = betsArray.size();

            for (Wt::Json::Object& bet: betsArray) {
                std::string oddsStr = bet["odds"].toString();
                float odds = std::stof(oddsStr);

                std::string wagerStr = bet["wager"].toString();
                float wager = std::stof(wagerStr);

                Bet newBet(odds, wager, bet["legs"].toString(), bet["success"].toBool());
                addBetRow(betTable, newBet);
            }
        }
    }
}

/**
 * @brief Function to remove zeroes from a float value
 * 
 * @param value 
 * @return std::string 
 */
std::string BettingTrack::removeZeroes(float value) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(8) << value;
    std::string str = out.str();

    // Remove trailing zeros
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);

    // If the decimal point is now the last character, remove that as well
    if (str.back() == '.') {
        str.pop_back();
    }

    return str;
}

/**
 * @brief Button switch
 * 
 */
void BettingTrack::onMainSwitch() {
    this->clear();
    switchToLeaderboardSignal.emit(loggedInUser_);
}

/**
 * @brief Creating a bet
 * 
 * @param betTable 
 */
void BettingTrack::createBet(Wt::WTable* betTable) {
    float odds = 0.0f;
    float wager = 0.0f;

    try {
        odds = std::stof(oddsEnter->text().toUTF8());
    } catch (const std::exception& e) {
        doJavaScript("alert('ERROR: Please ensure you enter numerical values');");
    }

    try {
        wager = std::stof(wagerEnter->text().toUTF8());
    } catch (const std::exception& e) {
        doJavaScript("alert('ERROR: Please ensure you enter numerical values');");
    }

    string legs = legsEnter->text().toUTF8();

    if (betSuccess->isChecked()) {
        success = true;
    } else {
        success = false;
    }


    oddsEnter->setText("");
    wagerEnter->setText("");
    legsEnter->setText("");
    betSuccess->setChecked(false);

    Bet newBet(odds, wager, legs, success);
    loggedInUser_.addBet(newBet);

    addBetRow(betTable, newBet);
    
    JsonDataManager jsonManager("UserData.json");
    Wt::Json::Array usersArray = jsonManager.readData();

    Wt::Json::Object bet;

    for ( Wt::Json::Object& user: usersArray) {
        if (user["username"] == loggedInUser_.getUsername().data()) {

            Wt::Json::Array& betsArray = user["bets"];
            int betCount = betsArray.size();

            bet["id"] = betCount + 1; 
            bet["odds"] = newBet.getOdds();
            bet["legs"] = newBet.getLegs().data();
            bet["wager"] = newBet.getWager();
            bet["success"] = newBet.getSuccess();

            betsArray.push_back(bet);

            //cout << "BETS: " << user["bets"].toString();

            jsonManager.writeData(usersArray);
            break;
        }
    }
}

/**
 * @brief Adding a bet row to the UI table 
 * 
 * @param table 
 * @param newBet 
 */
void BettingTrack::addBetRow(Wt::WTable* table, Bet newBet) {
    int row = table->rowCount();
    float payout = 0;

    if (newBet.getSuccess()) {
        payout = (newBet.getOdds() * newBet.getWager()) + newBet.getWager();
    } else {
        payout = 0 - newBet.getWager();
    }

    table->elementAt(row, 0)->addWidget(make_unique<Wt::WText>(newBet.getLegs()));
    table->elementAt(row, 0)->setAttributeValue("style", "border: 1px solid rgb(211, 211, 211)");
    table->elementAt(row, 1)->addWidget(make_unique<Wt::WText>(removeZeroes(newBet.getOdds())));
    table->elementAt(row, 1)->setAttributeValue("style", "border: 1px solid rgb(211, 211, 211)");
    table->elementAt(row, 2)->addWidget(make_unique<Wt::WText>("$" + removeZeroes(newBet.getWager())));
    table->elementAt(row, 2)->setAttributeValue("style", "border: 1px solid rgb(211, 211, 211)");
    table->elementAt(row, 3)->addWidget(make_unique<Wt::WText>(newBet.getSuccess() ? "WIN" : "LOSS"));
    table->elementAt(row, 3)->setAttributeValue("style", "border: 1px solid rgb(211, 211, 211)");
    table->elementAt(row, 4)->addWidget(make_unique<Wt::WText>("$" + removeZeroes(payout)));
    table->elementAt(row, 4)->setAttributeValue("style", "border: 1px solid rgb(211, 211, 211)");

}

/**
 * @brief Destroy the Betting Track:: Betting Track object
 * 
 */
BettingTrack::~BettingTrack() {};
