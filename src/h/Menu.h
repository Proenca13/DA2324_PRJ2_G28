//
// Created by joao on 12-05-2024.
//

#ifndef DA2324_PRJ2_G28_MENU_H
#define DA2324_PRJ2_G28_MENU_H

#include "Heuristics.h"
class Menu {
public:
    /**
     * @brief Default constructor implementation for the Menu class.
     */
    Menu();
    /**
     * @brief Displays the file selection menu and handles the user's choice.
     *
     * This function allows the user to select between toy graphs, fully connected graphs,
     * real world graphs, or manually enter file paths. Based on the user's selection,
     * the appropriate file paths are set, and the Heuristics object is initialized.
     */
    void menu_choose_file();
    /**
     * @brief Displays the toy graph selection menu and handles the user's choice.
     *
     * This function allows the user to select one of the predefined toy graphs (shipping, stadiums, tourism).
     * Based on the user's selection, the appropriate file path is set, and the Heuristics object is initialized.
     */
    void menu_choose_toy();
    /**
     * @brief Displays the main menu and handles the user's choice.
     *
     * This function provides options for running different algorithms and heuristics related to the Traveling Salesman Problem (TSP).
     * The user can choose to run the backtracking algorithm, triangular approximation heuristic, other heuristics, or exit the menu.
     */
    void Main_Menu();
private:
    Heuristics heuristics;
};


#endif //DA2324_PRJ2_G28_MENU_H
