/**
 * @file ComparisonTool.cpp
 * @author Cameron Maxwell
 * @brief The comaprison tool to compare players by displaying graphs of their stats
 * @version 1.0
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WPushButton.h>
#include <Wt/WEnvironment.h>
#include <Wt/WText.h>
#include <string.h>
#include <Wt/WCheckBox.h>
#include <Wt/WLineEdit.h>
#include <Wt/WSpinBox.h>
#include "ComparisonTool.h"

using namespace Wt;

/**
 * @brief Construct a new Comparison Tool:: Comparison Tool object
 * 
 * @param loggedInUser 
 */
ComparisonTool::ComparisonTool(const User& loggedInUser) : loggedInUser_(loggedInUser) {

    // Add page title, bold and center
    addNew<Wt::WText>("<div style='text-align:center; font-size: 24px; font-weight: bold;'>Comparison Tool!</div>");
    addWidget(std::make_unique<Wt::WBreak>());
    addWidget(std::make_unique<Wt::WBreak>());

    // Add centered subtitle
    addNew<Wt::WText>("<div style='text-align:center;'>Welcome to the Gridiron StatTrack Betting Tracker!</div>");
    addWidget(std::make_unique<Wt::WBreak>());

    // Add second centered subtitle
    addNew<Wt::WText>("<div style='text-align:center;'>Here you can select and compare two players of your choosing.</div>");
    addWidget(std::make_unique<Wt::WBreak>());
    addWidget(std::make_unique<Wt::WBreak>());

    // Labels
    addNew<Wt::WText>("Player Name: ");
    auto playerNameEdit = addNew<Wt::WLineEdit>();
    addWidget(std::make_unique<Wt::WBreak>());

    addNew<Wt::WText>("Touchdowns: ");
    auto touchdownsEdit = addNew<Wt::WLineEdit>();
    addWidget(std::make_unique<Wt::WBreak>());

    addNew<Wt::WText>("Yards: ");
    auto yardsEdit = addNew<Wt::WLineEdit>();
    addWidget(std::make_unique<Wt::WBreak>());

    addNew<Wt::WText>("Interceptions: ");
    auto interceptionsEdit = addNew<Wt::WLineEdit>();
    addWidget(std::make_unique<Wt::WBreak>());

    // Add submit button
    auto submitButton = addNew<Wt::WPushButton>("Submit");
    submitButton->clicked().connect([=] {
        // Get values from input fields
        Wt::WString playerName = playerNameEdit->text();
        int touchdowns = std::stoi(touchdownsEdit->text().toUTF8());
        int yards = std::stoi(yardsEdit->text().toUTF8());
        int interceptions = std::stoi(interceptionsEdit->text().toUTF8());

        // Create bar graph with entered values
        createBarGraph(playerName, touchdowns, yards, interceptions);
    });

    addWidget(std::make_unique<Wt::WBreak>());
    addWidget(std::make_unique<Wt::WBreak>());
    // Add Back Button
    auto backButton = addNew<Wt::WPushButton>("Back to Main Menu.");
    backButton->setMargin(50, Wt::Side::Left);
    backButton->setMargin(0, Wt::Side::Right);
    backButton->clicked().connect(this, &ComparisonTool::onMainSwitch);
}

/**
 * @brief Creating a bar graph for a player's stats
 * 
 * @param playerName 
 * @param touchdowns 
 * @param yards 
 * @param interceptions 
 */
void ComparisonTool::createBarGraph(const Wt::WString& playerName, int touchdowns, int yards, int interceptions) {


    // Create HTML content for the bar graph
    Wt::WString graphHtml = "<div style='margin: 200px;'>"
                            "<div style='text-align: center; font-weight: bold;'>" + playerName + "</div>"
                            "<div style='display: flex; align-items: flex-end;'>"
                            "<div style='background-color: #3498db; height: " + std::to_string(touchdowns) + "px; width: 150px;'></div>"
                            "<div style='margin: 0 5px;'><div>Touchdowns</div><div style='text-align: center;'>" + std::to_string(touchdowns) + "</div></div>"
                            "</div>"
                            "<div style='display: flex; align-items: flex-end;'>"
                            "<div style='background-color: #2ecc71; height: " + std::to_string(yards) + "px; width: 150px;'></div>"
                            "<div style='margin: 0 5px;'><div>Yards</div><div style='text-align: center;'>" + std::to_string(yards) + "</div></div>"
                            "</div>"
                            "<div style='display: flex; align-items: flex-end;'>"
                            "<div style='background-color: #e74c3c; height: " + std::to_string(interceptions) + "px; width: 150px;'></div>"
                            "<div style='margin: 0 5px;'><div>Interceptions</div><div style='text-align: center;'>" + std::to_string(interceptions) + "</div></div>"
                            "</div>"
                            "</div>";

    // Create a Wt::WText widget and add it to the container
    addWidget(std::make_unique<Wt::WText>(graphHtml));
}

/**
 * @brief Submit button for the tool to show the graph
 * 
 */
void ComparisonTool::onSubmit() {
    // Retrieve values from input fields
    std::string playerName = playerNameEdit_->text().toUTF8();
    int touchdowns = std::stoi(touchdownsEdit_->text().toUTF8());
    int yards = std::stoi(yardsEdit_->text().toUTF8());
    int interceptions = std::stoi(interceptionsEdit_->text().toUTF8());

    // Add Bar Graph with user input
    createBarGraph(playerName, touchdowns, yards, interceptions);
}

/**
 * @brief Main switch button
 * 
 */
void ComparisonTool::onMainSwitch() {
    this->clear();
    switchToLeaderboardSignal.emit(loggedInUser_);
}
/**
 * @brief Destroy the Comparison Tool:: Comparison Tool object
 * 
 */
ComparisonTool::~ComparisonTool() {};
