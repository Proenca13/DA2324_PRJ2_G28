//
// Created by joao on 12-05-2024.
//

#ifndef DA2324_PRJ2_G28_MENU_H
#define DA2324_PRJ2_G28_MENU_H

#include "Heuristics.h"
class Menu {
public:
    Menu();
    void  menu_choose_file();
    void   menu_choose_toy();
    void Main_Menu();
private:
    Heuristics heuristics;
};


#endif //DA2324_PRJ2_G28_MENU_H
