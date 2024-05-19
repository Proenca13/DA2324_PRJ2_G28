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
    /**
     * @brief Default constructor for Heuristics.
     */
    Heuristics();
    /**
     * @brief Constructs a Heuristics object and loads a toy graph from a file.
     * @param filepath The path to the file containing the graph data.
     */
    Heuristics(string filepath);
    /**
     * @brief Constructs a Heuristics object and loads a graph from files.
     * @param edgespath The path to the file containing the edges data.
     * @param nodespath The path to the file containing the nodes data.
     * @param is_real A flag indicating whether to load a real-world graph or an fully connected graph.
     */
    Heuristics(string edgespath,string nodespath,bool is_real);
    /**
     * @brief Executes the backtracking algorithm to solve TSP.
     * Prints the path, its distance, and the execution time.
     */
    void backtracking_algorithm();
    /**
     * @brief Executes the triangular approximation heuristic to solve TSP.
     * Prints the path, its distance, and the execution time.
     */
    void triangular_approximation_heuristic();
    /**
     * @brief Executes the nearest neighbor heuristic to solve TSP.
     * Prints the path, its distance, and the execution time.
     */
    void other_heuristic();
    vector<Vertex<int> *> odds();
private:
    Parser parser;
    Graph<int> graph;

};


#endif //DA2324_PRJ2_G28_HEURISTICS_H
