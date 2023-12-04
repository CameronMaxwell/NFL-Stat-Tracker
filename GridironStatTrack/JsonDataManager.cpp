/**
 * @file JsonDataManager.cpp
 * @author Cameron Maxwell
 * @brief The jsonDataManager that manages mulitple json files in the project
 * @version 1.0
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <Wt/Json/Parser.h>
#include <Wt/Json/Serializer.h>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "JsonDataManager.h"

/**
 * @brief Construct a new Json Data Manager:: Json Data Manager object
 * 
 * @param filename 
 */

JsonDataManager::JsonDataManager(const std::string& filename) : filename_(filename) {
    // Constructor may be used to initialize some properties, if necessary.
}

Wt::Json::Value JsonDataManager::readData() {
    std::ifstream inputFile(filename_);
    Wt::Json::Value jsonData;

    if (inputFile.is_open()) {
        std::string jsonContent((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
        inputFile.close();
        Wt::Json::parse(jsonContent, jsonData);
    }
    return jsonData;
}

void JsonDataManager::writeData(const Wt::Json::Value& data) {
    std::ofstream outputFile(filename_);

    const Wt::Json::Array& arr = data;
    
    std::string str = Wt::Json::serialize(arr);

    std::cout << "Data: " << str << std::endl;

    if (outputFile.is_open() && str.length() != 0 ) {
        std::string jsonContent = str;
        outputFile << jsonContent;
        outputFile.close();
    }
}
