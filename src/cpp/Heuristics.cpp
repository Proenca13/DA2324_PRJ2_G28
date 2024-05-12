//
// Created by joao on 12-05-2024.
//

#include "../h/Heuristics.h"
Heuristics::Heuristics() {}
Heuristics::Heuristics(std::string filepath) {
    if (filepath.find("Toy-Graphs") != std::string::npos) {
        graph = this->parser.loadToyGraph(filepath);
    }
    else{
        //graph = this->parser.loadRealWordGraph(filepath);
    }
}

void Heuristics::backtracking_algorithm() {}