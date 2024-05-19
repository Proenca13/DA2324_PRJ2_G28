//
// Created by joao on 12-05-2024.
//

#include "../h/Heuristics.h"
#include <chrono>
#define INF std::numeric_limits<double>::max()
Heuristics::Heuristics() {}
Heuristics::Heuristics(string filepath) {
    graph = this->parser.loadToyGraph(filepath);
}
Heuristics::Heuristics(string edgespath,string nodespath){
    graph = this->parser.loadRealWordGraph(edgespath,nodespath);
}
void Heuristics::backtracking_algorithm() {
    vector<int> path,solution;
    double solution_cost;
    double current_cost = 0;
    for (auto& vertex : graph.getVertexSet()) {
        vertex->setVisited(false);
    }
    auto vertex = graph.findVertex(0);
    solution_cost = INF;
    path.push_back(vertex->getInfo());
    vertex->setVisited(true);
    vertex->getAdj().front();
    auto start = std::chrono::high_resolution_clock::now();
    graph.tsp_backtracking(path,solution,solution_cost ,current_cost);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    for(auto v : solution){
        cout << v << "->" ;
    }
    cout << path.front()<<endl;
    cout << "The cost is: " << solution_cost << endl;
    cout << "Elapsed time: " << duration.count() << " ms" << endl;
}

void Heuristics::triangular_approximation_heuristic() {
    for (auto& vertex : graph.getVertexSet()) {
        vertex->setVisited(false);
    }
    std::queue<Vertex<int>*> path;
    auto start = std::chrono::high_resolution_clock::now();
    double dist = graph.triangularApproximation(path);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    while (!path.empty()){
        cout << path.front()->getInfo() << "->" ;
        path.pop();
    }
    cout << "\nThe cost is: " << dist << endl;
    cout << "Elapsed time: " << duration.count() << " ms" << endl;
}
void Heuristics::other_heuristic() {
    for (auto& vertex : graph.getVertexSet()) {
        vertex->setVisited(false);
    }
    std::vector<Vertex<int>*> path;
    auto start = std::chrono::high_resolution_clock::now();
    double dist;
    graph.nearestNeighborTSP(path,dist);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    for(auto v : path){
        cout << v->getInfo() << "->" ;

    }
    cout << "\nThe cost is: " << dist << endl;
    cout << "Elapsed time: " << duration.count() << " ms" << endl;
}