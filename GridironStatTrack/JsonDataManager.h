/**
 * @file JsonDataManager.h
 * @author Cameron Maxwell
 * @brief The header file for the jsonDataManager which manages the json files
 * @version 1.0
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <string>
#include <fstream>
#include <Wt/Json/Value.h>

// Guard to prevent multiple inclusions
#ifndef _JSONDATAMANAGER_
#define _JSONDATAMANAGER_

class JsonDataManager {
public:
    JsonDataManager(const std::string& filename);

    Wt::Json::Value readData();
    void writeData(const Wt::Json::Value& data);

private:
    const std::string filename_;
};

#endif
