/**
 * @file HelpPage.cpp
 * @author Cameron Maxwell
 * @brief The help page is used to answer frequent questions and help new users use the application.
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
#include "HelpPage.h"

/**
 * @brief Construct a new Help Page:: Help Page object
 * 
 * @param loggedInUser 
 */
HelpPage::HelpPage(const User& loggedInUser) : loggedInUser_(loggedInUser) {

  // Add page title, bold and center
  addNew<Wt::WText>("<div style='text-align:center; font-size: 24px; font-weight: bold;'>Help Page!</div>");
  addWidget(std::make_unique<Wt::WBreak>());
  addWidget(std::make_unique<Wt::WBreak>());

  // Add centered subtitle
  addNew<Wt::WText>("<div style='text-align:center;'>Welcome to the Gridiron StatTrack help page!</div>");
  addWidget(std::make_unique<Wt::WBreak>());

  // Add second centered subtitle
  addNew<Wt::WText>("<div style='text-align:center;'>Here you will find all the necessary information on how to use this website, as well as its many features.</div>");
  addWidget(std::make_unique<Wt::WBreak>());
  addWidget(std::make_unique<Wt::WBreak>());

  // Add About Information Button
  auto aboutButton = addNew<Wt::WPushButton>("About Gridiron StatTrack.");  // create a button
  aboutButton->setMargin(50, Wt::Side::Left);
  aboutButton->setMargin(0, Wt::Side::Right);                  // add 5 pixels margin

  // Add Function Information Button
  auto functionButton = addNew<Wt::WPushButton>("How to Use Gridiron StatTrack.");
  functionButton->setMargin(50, Wt::Side::Left);
  functionButton->setMargin(0, Wt::Side::Right);

  // Add Back Button
  auto backButton = addNew<Wt::WPushButton>("Back to Main Menu.");
  backButton->setMargin(50, Wt::Side::Left);
  backButton->setMargin(0, Wt::Side::Right);
  backButton->clicked().connect(this, &HelpPage::onMainSwitch);

  // Initialize About Information Text Box
  addWidget(std::make_unique<Wt::WBreak>()); 
  aboutInfo_ = addWidget(std::make_unique<Wt::WText>());

  // Initialize Function Information Text Box
  addWidget(std::make_unique<Wt::WBreak>());
  howToUse_ = addWidget(std::make_unique<Wt::WText>());

  // Add functionality to About Button using aboutUs method
  aboutButton->clicked().connect(this, &HelpPage::aboutUs);
  addWidget(std::make_unique<Wt::WBreak>());

  // Display About Information Text for About Button
  aboutButton->clicked().connect([=]() {
      std::cerr << "<div style='text-align:center;'>Gridiron StatTrack is a revolutionized way to get all data and statistics on your favourite sports leagues. "
                     "With a focus on American football, Gridiron StatTrack allows for users to select their favourite players and teams"
                     "and investigate their stats while also comparing the against each other. With hopes of expanding to other sports leagues"
                     "Gridiron StatTrack is looking to solidify itself as one of the main hubs for all things sports and stats.</div>" << std::endl;
  });
  addWidget(std::make_unique<Wt::WBreak>());

  // Add functionality to Function Button using howToUse method
  functionButton->clicked().connect(this, &HelpPage::howToUse);
  addWidget(std::make_unique<Wt::WBreak>());

  // Display How to Use Information Text for Function Button
  functionButton->clicked().connect([=]() {
      std::cerr << "<div style='text-align:center;'>Gridiron StatTrack Provides users with the tools to make their experience with the website as efficient and personal as possible. Upon creating your account,"
                       "you are able to favourite any number of players. For quick and easy access to all their stats and information use the search and sort features found on the main leaderboard page. Additionally, with our innovative"
                       "technology, you are able to compare players and their stats to understand how well players will preform. These tools can be applied"
                       "to managing fantasy teams, and to making more educated sports bets. Using our straight forward, user friendly website, all the information on all your favourite players is at your finger tips."
                       "You can also keep track of any bets you place using our betting tracker feature by simply inputting data into the provided fields.</div>" << std::endl;
  });
  addWidget(std::make_unique<Wt::WBreak>());

}

/**
 * @brief Prints a message about the Gridiron StatTrack application
 * 
 */
void HelpPage::aboutUs()
{

  // Sets the text in the AboutInfo text box
  aboutInfo_->setText("<div style='text-align:center;'>Gridiron StatTrack is a revolutionized way to get all data and statistics on your favourite sports leagues. "
                     "With a focus on American football, Gridiron StatTrack allows for users to select their favourite players and teams"
                     "and investigate their stats while also comparing the against each other. With hopes of expanding to other sports leagues"
                     "Gridiron StatTrack is looking to solidify itself as one of the main hubs for all things sports and stats.</div>");
  // Clears the howToUse text box
  howToUse_->setText(" ");
}

/**
 * @brief Prints a message about how to use the Gridiron StatTrack Application
 * 
 */
void HelpPage::howToUse()
{

    // Set the text in the howToUse text box
    howToUse_->setText("<div style='text-align:center;'>Gridiron StatTrack Provides users with the tools to make their experience with the website as efficient and personal as possible. Upon creating your account,"
                       "you are able to favourite any number of players. For quick and easy access to all their stats and information use the search and sort features found on the main leaderboard page. Additionally, with our innovative"
                       "technology, you are able to compare players and their stats to understand how well players will preform. These tools can be applied"
                       "to managing fantasy teams, and to making more educated sports bets. Using our straight forward, user friendly website, all the information on all your favourite players is at your finger tips."
                       "You can also keep track of any bets you place using our betting tracker feature by simply inputting data into the provided fields.</div>");

    // Clears the AboutInfo text box
    aboutInfo_->setText(" ");
}

/**
 * @brief Sends a signal to GridironStatTrack to switch to the leaderboard.
 * 
 */
void HelpPage::onMainSwitch(){
  this->clear();
  switchToLeaderboardSignal.emit(loggedInUser_);
}

/**
 * @brief Sets the logged in user of the application.
 * 
 * @param user 
 */
void HelpPage::setLoggedInUser(const User& user) {
    loggedInUser_ = user;
}

HelpPage::~HelpPage() {};
