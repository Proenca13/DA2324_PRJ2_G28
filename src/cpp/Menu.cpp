//
// Created by joao on 12-05-2024.
//

#include "../h/Menu.h"
#include <iostream>
using namespace std;
Menu::Menu() {};
void  Menu::menu_choose_file() {
    int c = true;
    string nodesfile,edgesfile;
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
            case 2:
                cout << "Please enter the number of edges: ";
                int number_edges;
                cin >> number_edges;
                nodesfile = "../Extra_Fully_Connected_Graphs/nodes.csv";
                edgesfile = "../Extra_Fully_Connected_Graphs/edges_" + to_string(number_edges) + ".csv";
                c = false;
                break;
            case 3:
                cout << "Please enter the number of the graph (from 1 to 3): ";
                int number_graph;
                cin >> number_graph;
                nodesfile = "../Real_World_Graphs/graph" + to_string(number_graph) + "/nodes.csv";
                edgesfile = "../Real_World_Graphs/graph" + to_string(number_graph) + "/edges.csv";
                c = false;
                break;
            case 4:
                cout << "Please enter the nodes file path: ";
                getline(cin>>ws,nodesfile);
                cout << "Please enter the edges file path: ";
                getline(cin>>ws,edgesfile);
                c = false;
                break;
            case 5:
                return;
            default:
                cout << "Invalid Input!\n";
                break;
        }
    }
    Heuristics heuristics(edgesfile,nodesfile);
    this->heuristics = heuristics;
    Main_Menu();
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
    this->heuristics = heuristics;
    Main_Menu();
}

void Menu::Main_Menu() {
    int c = true;
    while (c){
        cout << "---------------------------------------------" << endl;
        cout << "|Welcome to the Main Menu!                  |" << endl;
        cout << "|1. Backtracking Algorithm                  |" << endl;
        cout << "|2. Triangular Approximation Heuristic      |" << endl;
        cout << "|3. Other Heuristics                        |" << endl;
        cout << "|4. TSP in the Real World                   |" << endl;
        cout << "|5. Exit                                    |" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Choose an option: ";
        int option;
        cin >> option;
        switch (option) {
            case 1:
                heuristics.backtracking_algorithm();
                break;
            case 2:
                heuristics.triangular_approximation_heuristic();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                c = false;
                break;
            default:
                cout << "Invalid Input!\n";
                break;
        }
    }
}