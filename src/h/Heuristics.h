//
// Created by joao on 12-05-2024.
//

#ifndef DA2324_PRJ2_G28_HEURISTICS_H
#define DA2324_PRJ2_G28_HEURISTICS_H
#include "Parser.h"
#include <string>
#include "../../Data_Structures/Graph.h"
using namespace std;

class Heuristics {
public:
    Heuristics();
    Heuristics(string filepath);
    Heuristics(string edgespath,string nodespath);
    void backtracking_algorithm();
    void triangular_approximation_heuristic();
private:
    Parser parser;
    Graph<int> graph;

};


#endif //DA2324_PRJ2_G28_HEURISTICS_H
