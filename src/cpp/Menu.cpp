//
// Created by joao on 12-05-2024.
//

#include "../h/Menu.h"
#include <iostream>
using namespace std;
Menu::Menu() = default;
void Menu::menu_choose_file() {
    int c = true;
    string parsing;
    while (c){
        cout << "---------------------------------------------" << endl;
        cout << "|Select a parsing option                    |" << endl;
        cout << "|1. Toy Graphs                              |" << endl;
        cout << "|2. Fully Connected Graphs                  |" << endl;
        cout << "|3. Real World Graphs                       |" << endl;
        cout << "|4. Enter a file path                       |" << endl;
        cout << "|5. Exit                                    |" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Choose an option: ";
        int option;
        cin >> option;
        switch (option) {
            case 1:
                menu_choose_toy();
                break;
            case 4:
                cout << "Please enter the file path: ";
                getline(cin>>ws,parsing);
                c = false;
                break;
            case 5:
                c = false;
                break;
            default:
                cout << "Invalid Input!\n";
                break;
        }
    }
    Heuristics heuristics(parsing);
}

void Menu::menu_choose_toy() {
    int c = true;
    string parsing;
    while (c){
        cout << "---------------------------------------------" << endl;
        cout << "|Select a parsing option                    |" << endl;
        cout << "|1. Shipping.csv                            |" << endl;
        cout << "|2. Stadiums.csv                            |" << endl;
        cout << "|3. Tourism.csv                             |" << endl;
        cout << "|4. Exit                                    |" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Choose an option: ";
        int option;
        cin >> option;
        switch (option) {
            case 1:
                parsing = "../Toy-Graphs/shipping.csv";
                c = false;
                break;
            case 2:
                parsing = "../Toy-Graphs/stadiums.csv";
                c = false;
                break;
            case 3:
                parsing = "../Toy-Graphs/tourism.csv";
                c = false;
                break;
            case 4:
                c = false;
                break;
            default:
                cout << "Invalid Input!\n";
                break;
        }
    }
    Heuristics heuristics(parsing);
}