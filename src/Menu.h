//
// Created by oem on 16/05/23.
//

#ifndef DA___2ND_PROJECT_MENU_H
#define DA___2ND_PROJECT_MENU_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <chrono>
#include "FileReader.h"
#include "Services.h"


using namespace std;
namespace fs = std::filesystem;

/**
 * @brief The Menu class represents a menu for selecting data and functions.
 */

class Menu {

private:
    fs::directory_entry entry; /**< The selected directory entry */
    fs::path edges; /**< The path to the edges file */
    fs::path nodes; /**< The path to the nodes file */

public:

/**
 * Default constructor for the Menu class.
 *
 * @brief Default constructor for the Menu class.
 *
 * @note Initializes the `entry` member with the default ".././data" path.
 */

    Menu();

/**
 * Displays the Ocean Shipping and Urban Deliveries Management Program menu.
 *
 * @brief Displays the menu.
 */

    void Display();

/**
 * Selects the data based on the given directory entry.
 *
 * @brief Selects the data.
 * @param selected The directory entry.
 */

    void selectData(const fs::directory_entry& selected);

/**
 * Displays the options for selecting different algorithms and performs the selected algorithm based on user input.
 *
 * @brief Displays options and performs selected algorithm.
 */

    void selectFunctions();

/**
 * Sets the directory entry for the Menu class.
 *
 * @brief Sets the directory entry.
 * @param val The directory entry.
 */

    void setEntry(fs::directory_entry val);

/**
 * Sets the edges path for the Menu class.
 *
 * @brief Sets the edges path.
 * @param val The edges path.
 */

    void setEdges(fs::path val);

/**
 * Sets the nodes path for the Menu class.
 *
 * @brief Sets the nodes path.
 * @param val The nodes path.
 */

    void setNodes(fs::path val);
};


#endif //DA___2ND_PROJECT_MENU_H
